#include "UserCode/ICHiggsTauTau/Analysis/HiggsTauTau/interface/HTTWeights.h"
#include "UserCode/ICHiggsTauTau/interface/TriggerPath.hh"
#include "UserCode/ICHiggsTauTau/interface/TriggerObject.hh"
#include "UserCode/ICHiggsTauTau/interface/Electron.hh"
#include "UserCode/ICHiggsTauTau/interface/Muon.hh"
#include "UserCode/ICHiggsTauTau/interface/Tau.hh"
#include "UserCode/ICHiggsTauTau/interface/EventInfo.hh"
#include "UserCode/ICHiggsTauTau/Analysis/Utilities/interface/FnPredicates.h"
#include "UserCode/ICHiggsTauTau/Analysis/Utilities/interface/FnPairs.h"
#include "UserCode/ICHiggsTauTau/Analysis/Utilities/interface/BTagWeight.h"
#include "TMath.h"
#include "TSystem.h"
#include "TFile.h"


namespace ic {

  HTTWeights::HTTWeights(std::string const& name) : ModuleBase(name),
    channel_(channel::et),
    mc_(mc::summer12_53X),
    era_(era::data_2012_moriond) {
    do_trg_weights_     = false;
    trg_applied_in_mc_  = false;
    do_etau_fakerate_   = false;
    do_mtau_fakerate_   = false;
    do_idiso_weights_   = false;
    do_id_weights_      = false;
    do_emu_e_fakerates_   = false;
    do_emu_m_fakerates_   = false;
    do_top_factors_     = false;
    do_btag_weight_     = false;
    do_w_soup_          = false;
    do_dy_soup_          = false;
    ggh_mass_           = "";
  }

  HTTWeights::~HTTWeights() {
    ;
  }

  int HTTWeights::PreAnalysis() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "PreAnalysis Info for HTTWeights" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Channel: " << Channel2String(channel_) << std::endl;
    std::cout << "Era: " << Era2String(era_) << std::endl;
    std::cout << "MC: " << MC2String(mc_) << std::endl;
    std::cout << "Do Trg Weights?: \t\t" << do_trg_weights_ << std::endl;
    std::cout << "Trg Sel Applied?: \t\t" << trg_applied_in_mc_ << std::endl;
    std::cout << "Do ID & iso weights?: \t\t" << do_idiso_weights_ << std::endl;
    std::cout << "Do ID weights?: \t\t" << do_id_weights_ << std::endl;
    std::cout << "e->tau fake rate?: \t\t" << do_etau_fakerate_ << std::endl;
    std::cout << "m->tau fake rate?: \t\t" << do_mtau_fakerate_ << std::endl;
    std::cout << "e-mu elec fake rates?: \t\t" << do_emu_e_fakerates_ << std::endl;
    std::cout << "e-mu muon fake rates?: \t\t" << do_emu_m_fakerates_ << std::endl;
    std::cout << "e-mu TTBar scaling?: \t\t" << do_top_factors_ << std::endl;
    std::cout << "Generate b-tag weight?: \t" << do_btag_weight_ << std::endl;

    if (ggh_mass_ != "") {
      std::string file = "data/ggh_weights/weight_ptH_"+ggh_mass_+".root";
      std::cout << "Applying Higgs pT reweighting with: " << file << std::endl;
      ggh_weights_ = new TFile(file.c_str());
      gDirectory->cd("powheg_weight");
      ggh_hist_ = (TH1F*)gDirectory->Get(("weight_hqt_fehipro_fit_"+ggh_mass_).c_str());
    }

    muTauSF2011 = new TFile("data/scale_factors/hltScaleFactors_2011.root");
    hist_muTauSF2011 = (TH2D*)gDirectory->Get("LooseIsoPFTauRatio");
    hist_muTauSF2011PFTau10 = (TH2D*)gDirectory->Get("LooseIsoPFTau10PtEta");
    hist_muTauSF2011PFTau15 = (TH2D*)gDirectory->Get("LooseIsoPFTau15PtEta");
    hist_muTauSF2011PFTau20 = (TH2D*)gDirectory->Get("LooseIsoPFTau20PtEta");
    hist_muTauSF2011PFTau15MC = (TH2D*)gDirectory->Get("LooseIsoPFTau15PtEtaMC");

    if (do_emu_e_fakerates_ || do_emu_m_fakerates_) {
      if (era_ == era::data_2012_ichep || era_ == era::data_2012_hcp) {
        ElectronFRFile = new TFile("data/emu_fakerate/ElectronFakeRate_2012_12ifb.root");
        MuonFRFile = new TFile("data/emu_fakerate/MuonFakeRate_2012_12ifb.root");
      } else if (era_ == era::data_2012_donly || era_ == era::data_2012_moriond) {
        ElectronFRFile = new TFile("data/emu_fakerate/ElectronFakeRate_2012_19ifb.root");
        MuonFRFile = new TFile("data/emu_fakerate/MuonFakeRate_2012_19ifb.root");
      } else {
        ElectronFRFile = new TFile("data/emu_fakerate/ElectronFakeRate_2011.root");
        MuonFRFile = new TFile("data/emu_fakerate/MuonFakeRate_2011.root");
      }
      ElectronFakeRateHist_PtEta = (mithep::TH2DAsymErr*)(ElectronFRFile->Get("ElectronFakeRateDenominatorV4_Ele8CaloIdLCaloIsoVLCombinedSample_ptThreshold35_PtEta"));
      MuonFakeRateHist_PtEta = (mithep::TH2DAsymErr*)(MuonFRFile->Get("MuonFakeRateDenominatorV6_Mu8PtCombinedSample_ptThreshold25_PtEta"));
      ElectronFakeRateHist_PtEta->SetDirectory(0);
      MuonFakeRateHist_PtEta->SetDirectory(0);
      std::cout << "Muon: " << MuonFakeRateHist_PtEta->GetXaxis()->GetXmin() << "\t"
                            << MuonFakeRateHist_PtEta->GetXaxis()->GetXmax() << "\t"
                            << MuonFakeRateHist_PtEta->GetYaxis()->GetXmin() << "\t"
                            << MuonFakeRateHist_PtEta->GetYaxis()->GetXmax() << std::endl;
      std::cout << "Electron: " << ElectronFakeRateHist_PtEta->GetXaxis()->GetXmin() << "\t"
                                << ElectronFakeRateHist_PtEta->GetXaxis()->GetXmax() << "\t"
                                << ElectronFakeRateHist_PtEta->GetYaxis()->GetXmin() << "\t"
                                << ElectronFakeRateHist_PtEta->GetYaxis()->GetXmax() << std::endl;

    }

    if (do_w_soup_) {
      std::cout << "Making W Soup:" << std::endl;
      std::cout << "nInc = " << n_inc_ << std::endl;
      w1_ = (n_inc_*f1_) / ( (n_inc_*f1_) + n1_ );
      w2_ = (n_inc_*f2_) / ( (n_inc_*f2_) + n2_ );
      w3_ = (n_inc_*f3_) / ( (n_inc_*f3_) + n3_ );
      w4_ = (n_inc_*f4_) / ( (n_inc_*f4_) + n4_ );
      std::cout << "f1 = " << f1_ << "\t" << "n1 = " << n1_ << "\t" << "w1 = " << w1_ << std::endl;
      std::cout << "f2 = " << f2_ << "\t" << "n2 = " << n2_ << "\t" << "w2 = " << w2_ << std::endl;
      std::cout << "f3 = " << f3_ << "\t" << "n3 = " << n3_ << "\t" << "w3 = " << w3_ << std::endl;
      std::cout << "f4 = " << f4_ << "\t" << "n4 = " << n4_ << "\t" << "w4 = " << w4_ << std::endl;
    }
    if (do_dy_soup_) {
      std::cout << "Making DY Soup:" << std::endl;
      std::cout << "nInc = " << zn_inc_ << std::endl;
      zw1_ = (zn_inc_*zf1_) / ( (zn_inc_*zf1_) + zn1_ );
      zw2_ = (zn_inc_*zf2_) / ( (zn_inc_*zf2_) + zn2_ );
      zw3_ = (zn_inc_*zf3_) / ( (zn_inc_*zf3_) + zn3_ );
      zw4_ = (zn_inc_*zf4_) / ( (zn_inc_*zf4_) + zn4_ );
      std::cout << "f1 = " << zf1_ << "\t" << "n1 = " << zn1_ << "\t" << "w1 = " << zw1_ << std::endl;
      std::cout << "f2 = " << zf2_ << "\t" << "n2 = " << zn2_ << "\t" << "w2 = " << zw2_ << std::endl;
      std::cout << "f3 = " << zf3_ << "\t" << "n3 = " << zn3_ << "\t" << "w3 = " << zw3_ << std::endl;
      std::cout << "f4 = " << zf4_ << "\t" << "n4 = " << zn4_ << "\t" << "w4 = " << zw4_ << std::endl;
    }
    return 0;
  }

  int HTTWeights::Execute(TreeEvent *event) {

    std::vector<CompositeCandidate *> const& dilepton = event->GetPtrVec<CompositeCandidate>("emtauCandidates");

    double weight = 1.0;
    EventInfo * eventInfo = event->GetPtr<EventInfo>("eventInfo");

    if (ggh_mass_ != "") {
      std::vector<GenParticle *> const& parts = event->GetPtrVec<GenParticle>("genParticles");
      GenParticle const* higgs = NULL;
      for (unsigned i = 0; i < parts.size(); ++i) {
        if (parts[i]->status() == 3 && parts[i]->pdgid() == 25) {
          higgs = parts[i];
          break;
        }
      }
      if (!higgs) {
        std::cout << "Higgs not found!" << std::endl;
        throw;
      }
      double h_pt = higgs->pt();
      double pt_weight = 1.0;
      int fbin = ggh_hist_->FindBin(h_pt);
      if (fbin > 0 && fbin <= ggh_hist_->GetNbinsX()) {
        pt_weight =  ggh_hist_->GetBinContent(fbin);
        //std::cout << "pt: " << h_pt << "\tweight: " <<  pt_weight << std::endl;
      }
      eventInfo->set_weight("ggh", pt_weight);
    }

    if (do_top_factors_) {
      std::vector<PFJet*> jets = event->GetPtrVec<PFJet>("pfJetsPFlow"); // Make a copy of the jet collection
      ic::erase_if(jets,!boost::bind(MinPtMaxEta, _1, 30.0, 4.7));
      if (era_ >= era::data_2012_ichep) {
        double top_factor = 1.0; // For 0-jet we'll scale by 0.97 in the datacard creation
        if (jets.size() == 1) top_factor = 0.97938; // 0.097938 * 0.97 = 0.95
        if (jets.size() > 1) top_factor = 0.90721; // 0.90721 * 0.97 = 0.88
        eventInfo->set_weight("top_factor", top_factor);
      }
    }
    

    if (do_btag_weight_) {
      std::vector<PFJet*> jets = event->GetPtrVec<PFJet>("pfJetsPFlow"); // Make a copy of the jet collection
      ic::erase_if(jets,!boost::bind(MinPtMaxEta, _1, 20.0, 2.4));
      //double no_btag_weight = btag_weight.GetWeight(jets, "CSVM", 0, 0, is_2012_);
      //double inclusive_btag_weight = btag_weight.GetWeight(jets, "CSVM", 1, 99, is_2012_);
      double no_btag_weight = 1.0;
      double inclusive_btag_weight = 1.0;
      btag_weight.ReTag(jets, mc_ == mc::summer12_53X);
      event->Add("no_btag_weight", no_btag_weight);
      event->Add("inclusive_btag_weight", inclusive_btag_weight);
    }

    if (do_trg_weights_) {
      if (channel_ == channel::et) {
        Electron const* elec = dynamic_cast<Electron const*>(dilepton[0]->GetCandidate("lepton1"));
        Tau const* tau = dynamic_cast<Tau const*>(dilepton[0]->GetCandidate("lepton2"));
        double e_pt = elec->pt();
        double e_eta = fabs(elec->sc_eta());
        double t_pt = tau->pt();
        double t_eta = fabs(tau->eta());
        double ele_trg = 1.0;
        double tau_trg = 1.0;
        double ele_trg_mc = 1.0;
        double tau_trg_mc = 1.0;
        if (mc_ == mc::summer12_53X) {
          double edata20A  = 1.0;
          double edata22B  = 1.0;
          double edata22C  = 1.0;
          double edata22D  = 1.0;
          double edataABCD = 1.0;
          double emc22ABC  = 1.0;
          double emc22ABCD = 1.0;
          if (e_eta < 1.479) {
            edata20A   = Efficiency(e_pt, 20.4669, 1.20429, 1.84954, 1.38645, 0.891122);
            edata22B   = Efficiency(e_pt, 22.8618, 0.844755, 1.07941, 1.27956, 1.07722);
            edata22C   = Efficiency(e_pt, 22.8598, 0.855666, 1.02951, 1.32713, 1.05486);
            edata22D   = Efficiency(e_pt, 23.0825, 0.930633, 1.17931, 1.19807, 1.19376);
            edataABCD  = Efficiency(e_pt, 22.9041, 1.04728, 1.38544, 1.22576, 1.13019);
            emc22ABC   = Efficiency(e_pt, 21.4136, 0.000422, 0.000002473, 1.42487, 1.00104); // MC Reweighted to ABC
            emc22ABCD  = Efficiency(e_pt, 21.7243, 0.619015, 0.739301, 1.34903, 1.02594); // MC Reweighted to ABCD
          } else {
            edata20A   = Efficiency(e_pt, 21.4136, 1.93922, 2.43562, 1.00186, 51.947);
            edata22B   = Efficiency(e_pt, 22.1045, 1.08481, 0.780119, 1.91846, 0.962174);
            edata22C   = Efficiency(e_pt, 21.7643, 1.45024, 0.785753, 3.14722, 0.926788);
            edata22D   = Efficiency(e_pt, 21.8373, 1.26926, 0.801134, 2.27808, 0.938937);
            edataABCD  = Efficiency(e_pt, 21.9941, 1.43419, 1.01152, 2.28622, 0.939872);
            emc22ABC   = Efficiency(e_pt, 20.9985, 0.002918, 0.000034313, 1.41479, 1.06506); // MC Reweighted to ABC
            emc22ABCD  = Efficiency(e_pt, 22.1217, 1.34054, 1.8885, 1.01855, 4.7241); // MC Reweighted to ABCD
          }
          if (era_ == era::data_2012_ichep) {
            ele_trg = (0.14 * edata20A) + (0.86 * edata22B);
            ele_trg_mc = emc22ABC;
          }
          if (era_ == era::data_2012_hcp) {
            ele_trg = (0.061 * edata20A) + (0.373 * edata22B) + (0.566 * edata22C);
            ele_trg_mc = emc22ABC;
          }
          if (era_ == era::data_2012_moriond) {
            ele_trg = edataABCD;
            ele_trg_mc = emc22ABCD;
          }
          if (era_ == era::data_2012_donly) {
            ele_trg = edata22D;
            ele_trg_mc = emc22ABCD;
          }

          double tdata20A   = 1.0;
          double tdata20B   = 1.0;
          double tdata20ABC = 1.0;
          double tdataABCD  = 1.0;
          double tmc20AB    = 1.0;
          double tmc20ABC   = 1.0;
          double tmcABCD    = 1.0;

          if (t_eta < 1.5) {
            tdata20A    = Efficiency(t_pt, 18.84658959, 0.25958704, 0.17300958, 2.43491208, 0.85872017);
            tdata20B    = Efficiency(t_pt, 18.48663118, 1.63417147, 20.25695815, 138.55422224, 0.89456038);
            tdata20ABC  = Efficiency(t_pt, 18.43442868, 2.08967536, 3.27357845, 6.96327309, 0.85564484);
            tdataABCD   = Efficiency(t_pt, 18.686211,   1.993524,  3.202713,  3.612693,  0.871640);
            tmc20AB     = Efficiency(t_pt, 18.77448606, 0.45765507, 0.26077509, 13.43372485, 0.88037836);
            tmc20ABC    = Efficiency(t_pt, 18.40815138, 1.53235636, 3.55989632, 1.74542709, 0.90118450);
            tmcABCD     = Efficiency(t_pt, 18.431118,   1.572877,  3.301699,  4.760769,  0.899620);
          } else {
            tdata20A    = Efficiency(t_pt, 18.84658959, 0.25958704, 0.17300958, 2.43491208, 0.85872017);
            tdata20B    = Efficiency(t_pt, 18.48663118, 1.63417147, 20.25695815, 138.55422224, 0.89456038);
            tdata20ABC  = Efficiency(t_pt, 18.16839440, 1.86184564, 4.39116712, 1.01410741, 1.39240481);
            tdataABCD   = Efficiency(t_pt, 18.472954,   1.606388,  3.468975,  55.629620,   0.828977);
            tmc20AB     = Efficiency(t_pt, 18.77448606, 0.45765507, 0.26077509, 13.43372485, 0.88037836);
            tmc20ABC    = Efficiency(t_pt, 18.29028052, 1.56239255, 11.03605631, 155.89290151, 0.85683995);
            tmcABCD     = Efficiency(t_pt, 18.257217,   1.632443,  9.283116,  40.219585,  0.858643);
          }
          if (era_ == era::data_2012_ichep) {
            tau_trg = (0.14 * tdata20A) + (0.86 * tdata20B);
            tau_trg_mc = tmc20AB;
          }
          if (era_ == era::data_2012_hcp) {
            tau_trg = tdata20ABC;
            tau_trg_mc = tmc20ABC;
          }
          if (era_ == era::data_2012_moriond || era_ == era::data_2012_donly) {
            tau_trg = tdataABCD;
            tau_trg_mc = tmcABCD;
          }

        } else if (mc_ == mc::fall11_42X) {
          if (fabs(e_eta) < 1.479) {
            double ele15_eb = Efficiency(e_pt, 14.8772, 0.311255, 0.221021, 1.87734, 0.986665);
            double ele18_eb = Efficiency(e_pt, 18.3193, 0.443703, 0.385554, 1.86523, 0.986514);
            double ele20_eb = Efficiency(e_pt, 20.554, 0.683776, 0.855573, 1.45917, 1.03957);
            ele_trg = (0.41 * ele15_eb) + (0.39 * ele18_eb) + (0.2 * ele20_eb);
            ele_trg_mc = Efficiency(e_pt, 15.1804, 2.43126, 3.85048, 1.72284, 0.998507);
          } else {
            double ele15_ee = Efficiency(e_pt, 15.6629, 0.759192, 0.47756, 2.02154, 0.998816);
            double ele18_ee = Efficiency(e_pt, 19.6586, 0.682633, 0.279486, 2.66423, 0.973455);
            double ele20_ee = Efficiency(e_pt, 23.6386, 1.60775, 1.72093, 1.4131, 1.13962);
            ele_trg = (0.41 * ele15_ee) + (0.39 * ele18_ee) + (0.2 * ele20_ee);
            ele_trg_mc = Efficiency(e_pt, 16.993, 0.0693958, 0.00695096, 1.9566, 1.00632);
          }
          if (fabs(t_eta) < 1.5) {
            double tau20l_eb = Efficiency(t_pt, 19.3916,  0.996964,  1.70131,   1.38002,   0.903245);
            double tau20m_eb = Efficiency(t_pt, 19.5667,  1.15203 ,  1.68126,   1.40025,   0.848033);
            double tau20t_eb = Efficiency(t_pt, 19.6013,  0.987317,  1.08015,   1.88592,   0.776894);
            tau_trg = (0.25 * tau20l_eb) + (0.59 * tau20m_eb) + (0.16 * tau20t_eb);
            tau_trg_mc = Efficiency(t_pt, 19.468, 0.0615381, 0.0349325, 1.59349, 0.860096);
          } else {
            double tau20l_ee = Efficiency(t_pt, 18.8166,  0.526632,  0.20666,   6.80392,   0.903245);
            double tau20m_ee = Efficiency(t_pt, 18.8476,  0.528963,  0.16717,   3.65814,   0.749759);
            double tau20t_ee = Efficiency(t_pt, 18.8859,  0.271301,  0.128008,  1.50993,   0.825122);
            tau_trg = (0.25 * tau20l_ee) + (0.59 * tau20m_ee) + (0.16 * tau20t_ee);
            tau_trg_mc = Efficiency(t_pt, 19.3862, 0.247148, 0.123187, 2.87108, 0.790894);
          }
        }
        if (trg_applied_in_mc_) {
          ele_trg = ele_trg / ele_trg_mc;
          tau_trg = tau_trg / tau_trg_mc;
        }
        weight *= (ele_trg * tau_trg);
        event->Add("trigweight_1", ele_trg);
        event->Add("trigweight_2", tau_trg);
      } else if (channel_ == channel::mt) {
        Muon const* muon = dynamic_cast<Muon const*>(dilepton[0]->GetCandidate("lepton1"));
        double pt = muon->pt();
        double m_eta = fabs(muon->eta());
        double m_a_eta = muon->eta();
        Tau const* tau = dynamic_cast<Tau const*>(dilepton[0]->GetCandidate("lepton2"));
        double t_pt = tau->pt();
        double t_eta = fabs(tau->eta());
        double mu_trg = 1.0;
        double tau_trg = 1.0;
        double mu_trg_mc = 1.0;
        double tau_trg_mc = 1.0;
        if (mc_ == mc::summer12_53X) {
          double mu18A = 1.0;
          double mu17B = 1.0;
          double mu17C = 1.0;
          double mu17D = 1.0;
          double muABCD = 1.0;
          double mcABC = 1.0;
          double mcABCD = 1.0;
          if (m_a_eta >= 0 && m_a_eta < 0.8) {
            mu18A   = Efficiency(pt, 17.9605, 0.500059, 0.865294, 1.04633, 1.69027);
            mu17B   = Efficiency(pt, 15.9829, 0.0435624, 0.0196399, 1.71605, 0.967839);
            mu17C   = Efficiency(pt, 15.9762, 0.0552286, 0.0231409, 1.78576, 0.96848);
            mu17D   = Efficiency(pt, 15.9894, 0.0362229, 0.0132101, 1.65758, 0.975996);
            muABCD  = Efficiency(pt, 15.9802, 0.0548775, 0.020313, 1.79791, 0.968398);
            mcABC   = Efficiency(pt, 15.9618, 0.0587497, 0.0189749, 1.94016, 0.978294);
            mcABCD  = Efficiency(pt, 15.9289, 0.0271317, 0.00448573, 1.92101, 0.978625);
          } else if (m_a_eta >= 0.8 && m_a_eta < 1.2) {
            mu18A   = Efficiency(pt, 18.094, 0.607997, 0.89385, 1.36337, 0.92399);
            mu17B   = Efficiency(pt, 17.4688, 0.0494554, 0.0628053, 1.34067, 0.904989);
            mu17C   = Efficiency(pt, 17.462, 0.804351, 1.62323, 1.22776, 0.900085);
            mu17D   = Efficiency(pt, 16.5276, 0.28491, 0.342352, 1.49551, 0.894305);
            muABCD  = Efficiency(pt, 16.8396, 0.458636, 0.633185, 1.5706, 0.8848);
            mcABC   = Efficiency(pt, 16.7859, 0.443337, 0.571078, 1.62214, 0.919211);
            mcABCD  = Efficiency(pt, 16.5678, 0.328333, 0.354533, 1.67085, 0.916992);
          } else if (m_a_eta >= 1.2) {
            mu18A   = Efficiency(pt, 16.9805, 0.00009184, 0.000000028, 1.83783, 0.858988);
            mu17B   = Efficiency(pt, 16.0029, 0.000040186, 0.000000066, 1.42189, 0.880251);
            mu17C   = Efficiency(pt, 16.0051, -0.000041024, 0.000000012, 1.82463, 0.865417);
            mu17D   = Efficiency(pt, 17.184, -1.44981, 3.08139, 1.01062, 2.25017);
            muABCD  = Efficiency(pt, 15.9987, 8.94398e-05, 5.18549e-08, 1.8342, 0.854625);
            mcABC   = Efficiency(pt, 15.9974, 0.000085057, 0.000000055, 1.64714, 0.888026);
            mcABCD  = Efficiency(pt, 15.997, 7.90069e-05, 4.40036e-08, 1.66272, 0.884502);
          } else if (m_a_eta >= -0.8 && m_a_eta < 0) {
            mu18A   = Efficiency(pt, 17.2736, 0.13896, 0.198452, 1.13119, 1.21897);
            mu17B   = Efficiency(pt, 16.4569, 0.214484, 0.302707, 1.42363, 0.982643);
            mu17C   = Efficiency(pt, 15.9788, 0.044455, 0.0215911, 1.71024, 0.965673);
            mu17D   = Efficiency(pt, 15.9819, 0.0376022, 0.0180587, 1.58457, 0.97677);
            muABCD  = Efficiency(pt, 15.9828, 0.0412999, 0.0177441, 1.66934, 0.970097);
            mcABC   = Efficiency(pt, 15.959, 0.0229759, 0.00597735, 1.76124, 0.980734);
            mcABCD  = Efficiency(pt, 15.9556, 0.0236127, 0.00589832, 1.75409, 0.981338);
          } else if (m_a_eta >= -1.2 && m_a_eta < -0.8) {
            mu18A   = Efficiency(pt, 16.9824, 0.0694986, 0.0186614, 1.66577, 0.908218);
            mu17B   = Efficiency(pt, 18.015, 0.0512973, 0.0603545, 1.36001, 0.907481);
            mu17C   = Efficiency(pt, 17.446, 0.760355, 1.58032, 1.0623, 1.10472);
            mu17D   = Efficiency(pt, 17.1986, 0.649411, 1.0234, 1.45531, 0.888363);
            muABCD  = Efficiency(pt, 17.3283, 0.707103, 1.2047, 1.3732, 0.900519);
            mcABC   = Efficiency(pt, 17.3339, 0.768105, 1.31172, 1.35161, 0.942887);
            mcABCD  = Efficiency(pt, 17.3135, 0.747636, 1.21803, 1.40611, 0.934983);
          } else if (m_a_eta < -1.2) {
            mu18A   = Efficiency(pt, 16.9993, 0.00008822, 0.000000079, 1.40792, 0.928102);
            mu17B   = Efficiency(pt, 16.0015, 0.00000056, 0.000000134, 1.37357, 0.891284);
            mu17C   = Efficiency(pt, 15.9974, 0.000072034, 0.000000077, 1.5461, 0.87064);
            mu17D   = Efficiency(pt, 16.6377, -1.23117, 2.14735, 1.17365, 0.957028);
            muABCD  = Efficiency(pt, 15.9825, 7.90724e-05, 5.49275e-08, 1.6403, 0.858285);
            mcABC   = Efficiency(pt, 15.997, 0.000087304, 0.000000054, 1.67934, 0.871415);
            mcABCD  = Efficiency(pt, 16.0051, 2.45144e-05, 4.3335e-09, 1.66134, 0.87045);
          }
          if (era_ == era::data_2012_ichep) {
            mu_trg = (0.14 * mu18A) + (0.86 * mu17B);
            mu_trg_mc = mcABC;
          }
          if (era_ == era::data_2012_hcp) {
            mu_trg = (0.061 * mu18A) + (0.373 * mu17B) + (0.566 * mu17C);
            mu_trg_mc = mcABC;
          }
          if (era_ == era::data_2012_moriond) {
            mu_trg = muABCD;
            mu_trg_mc = mcABCD;
          }
          if (era_ == era::data_2012_donly) {
            mu_trg = mu17D;
            mu_trg_mc = mcABCD;
          }

          double tdata20A    = 1.0;
          double tdata20B    = 1.0;
          double tdata20ABC  = 1.0;
          double tdataABCD   = 1.0;
          double tmc20AB     = 1.0;
          double tmc20ABC    = 1.0;
          double tmcABCD    = 1.0;
          if (fabs(t_eta) < 1.5) {
            tdata20A   = Efficiency(t_pt, 18.52262128, 1.85879597, 3.48843815, 1.15491294, 1.02489024);
            tdata20B   = Efficiency(t_pt, 17.92648563, 1.96846742, 4.46406075, 1.02023992, 1.52260575);
            tmc20AB    = Efficiency(t_pt, 18.86257072, 0.25680380, 0.16916101, 2.42931257, 0.89590264);
            tdata20ABC = Efficiency(t_pt, 18.50940288, 1.62285299, 2.73232995, 1.79135412, 0.91481432);
            tmc20ABC   = Efficiency(t_pt, 18.80484409, 0.19082817, 0.19983010, 1.81979820, 0.93270649);
            tdataABCD  = Efficiency(t_pt, 18.52036251,  1.47760312,  2.53574445,  1.71202550,  0.93019930);
            tmcABCD    = Efficiency(t_pt, 18.88740627,  0.10718873,  0.12277723,  1.60581265,  0.95041892);

          } else {
            tdata20A   = Efficiency(t_pt, 18.90119559, 0.14025596, 0.14482632, 1.56126508, 0.81188198);
            tdata20B   = Efficiency(t_pt, 18.59856420, 2.49132550, 10.99643595, 1.50651123, 0.87952970);
            tmc20AB    = Efficiency(t_pt, 18.74764561, 1.82036845, 701.46994969, 101.57913480, 0.82547043);
            tdata20ABC = Efficiency(t_pt, 18.45678784, 0.68697618, 0.57008697, 3.73470825, 0.84747211);
            tmc20ABC   = Efficiency(t_pt, 18.25975478, 1.32745225, 1.70380810, 149.18410074, 0.87377770);
            tdataABCD  = Efficiency(t_pt, 18.41225333,  0.76598912,  0.60544260,  5.38350881,  0.85870108);
            tmcABCD    = Efficiency(t_pt, 18.30439676,  1.44360240,  3.79358997,  1.07560564,  0.93103925);
          }
          if (era_ == era::data_2012_ichep) {
              tau_trg = (0.14 * tdata20A) + (0.86 * tdata20B);
              tau_trg_mc = tmc20AB;
          }
          if (era_ == era::data_2012_hcp) {
            tau_trg = tdata20ABC;
            tau_trg_mc = tmc20ABC;
          }
          if (era_ == era::data_2012_moriond || era_ == era::data_2012_donly) {
            tau_trg = tdataABCD;
            tau_trg_mc = tmcABCD;
          }
        } else if (mc_ == mc::fall11_42X) {
          if (fabs(m_eta) < 1.4) {
            double mu1215_eb = 0.901;
            double mu15_2p1_eb = Efficiency(pt, 15.06,  0.55278,   1.34236,   1.003,   3.36767);
            mu_trg = (0.402 * mu1215_eb) + (0.598 * mu15_2p1_eb);
            mu_trg_mc = 0.917;
          } else {
            double mu1215_ee = 0.863;
            double mu15_2p1_ee = Efficiency(pt, 15.03175,   0.866114,  1.25009,   1.63711,   0.844906);
            mu_trg = (0.402 * mu1215_ee) + (0.598 * mu15_2p1_ee);  
            mu_trg_mc = 0.836;      
          }
          if (fabs(t_eta) < 1.5) {
            double tau10l_eb = Efficiency(t_pt, 13.6046,   1.66291,   1.71551,   141.929,   0.910686);
            double tau15l_eb = Efficiency(t_pt, 13.9694,   0.084835,  0.057743,  1.50674,   0.984976);
            double tau20l_eb = Efficiency(t_pt, 19.2102,   1.26519,   2.48994,   1.04699,  1.3492);
            tau_trg = (0.043 * tau10l_eb) + (0.359 * tau15l_eb) + (0.598 * tau20l_eb);
            tau_trg_mc = Efficiency(t_pt, 14.4601, 0.0485272, 0.03849, 1.48324, 0.965257);
          } else {
            double tau10l_ee = Efficiency(t_pt, -0.392211,   7.90467,   5.48228,   134.599,   0.925858);
            double tau15l_ee = Efficiency(t_pt, 14.435,  1.34952,   2.43996,   1.03631,   1.79081);
            double tau20l_ee = Efficiency(t_pt, 19.2438,   1.37298,   1.76448,   1.73935,   0.901291);
            tau_trg = (0.043 * tau10l_ee) + (0.359 * tau15l_ee) + (0.598 * tau20l_ee);
            tau_trg_mc = Efficiency(t_pt, 14.4451, 0.0790573, 0.0732472, 1.47046, 0.942028);
          }
        }
        if (trg_applied_in_mc_) {
          mu_trg = mu_trg / mu_trg_mc;
          tau_trg = tau_trg / tau_trg_mc;
        }
        weight *= (mu_trg * tau_trg);
        event->Add("trigweight_1", mu_trg);
        event->Add("trigweight_2", tau_trg);
      } else if (channel_ == channel::em) {
        Electron const* elec = dynamic_cast<Electron const*>(dilepton[0]->GetCandidate("lepton1"));
        Muon const* muon = dynamic_cast<Muon const*>(dilepton[0]->GetCandidate("lepton2"));
        double e_pt = elec->pt();
        double e_eta = fabs(elec->sc_eta());
        double m_pt = muon->pt();
        double m_eta = fabs(muon->eta());
        double m_trg = 1.0;
        double m_trg_mc = 1.0;
        double e_trg = 1.0;
        double e_trg_mc = 1.0;
        if (mc_ == mc::summer12_53X) {
          if (era_ == era::data_2012_ichep) {
            if (m_eta < 0.8) {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9873; m_trg = 0.9716; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9876; m_trg = 0.9777; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9883; m_trg = 0.9784; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9892; m_trg = 0.9621; }
              if (m_pt > 30.0)                 { m_trg_mc = 0.9747; m_trg = 0.9726; }
            } else if (m_eta >= 0.8 && m_eta < 1.2) {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9688; m_trg = 0.9458; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9505; m_trg = 0.9319; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9925; m_trg = 0.9161; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9667; m_trg = 0.9489; }
              if (m_pt > 30.0)                 { m_trg_mc = 0.9671; m_trg = 0.9111; }
            } else {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9374; m_trg = 0.9100; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9559; m_trg = 0.9459; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9666; m_trg = 0.9291; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9392; m_trg = 0.9035; }
              if (m_pt > 30.0)                 { m_trg_mc = 0.9563; m_trg = 0.9075; }
            }
            if (e_eta < 0.8) {
              if (e_pt <= 15.0)                { e_trg_mc = 0.7919; e_trg = 0.7925;}
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.9091; e_trg = 0.9023;}
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9502; e_trg = 0.9213;}
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9629; e_trg = 0.9468;}
              if (e_pt > 30.0)                 { e_trg_mc = 0.9609; e_trg = 0.9661;}
            } else if (e_eta >= 0.8 && e_eta < 1.479) {
              if (e_pt <= 15.0)                { e_trg_mc = 0.8268; e_trg = 0.7472;}
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.9513; e_trg = 0.9299;}
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9844; e_trg = 0.9496;}
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9776; e_trg = 0.9796;}
              if (e_pt > 30.0)                 { e_trg_mc = 0.9800; e_trg = 0.9795;}
            } else {
              if (e_pt <= 15.0)                { e_trg_mc = 0.7596; e_trg = 0.7378;} 
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.9240; e_trg = 0.8869;}
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9632; e_trg = 0.9228;}
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9803; e_trg = 0.9550;}
              if (e_pt > 30.0)                 { e_trg_mc = 0.9850; e_trg = 0.9751;}
            }
          }
          if (era_ == era::data_2012_hcp) {
            if (m_eta < 0.8) {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9873; m_trg = 0.9693; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9876; m_trg = 0.9659; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9883; m_trg = 0.9758; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9892; m_trg = 0.9650; }
              if (m_pt > 30.0)                 { m_trg_mc = 0.9747; m_trg = 0.9704; }
            } else if (m_eta >= 0.8 && m_eta < 1.2) {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9688; m_trg = 0.9411; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9505; m_trg = 0.9298; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9925; m_trg = 0.9460; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9667; m_trg = 0.9492; }
              if (m_pt > 30.0)                 { m_trg_mc = 0.9671; m_trg = 0.9326; }
            } else {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9374; m_trg = 0.9069; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9559; m_trg = 0.9164; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9666; m_trg = 0.9284; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9392; m_trg = 0.9046; }
              if (m_pt > 30.0)                 { m_trg_mc = 0.9563; m_trg = 0.9114; }
            }
            if (e_eta < 0.8) {
              if (e_pt <= 15.0)                { e_trg_mc = 0.7919; e_trg = 0.7633;}
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.9091; e_trg = 0.8874;}
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9502; e_trg = 0.9200;}
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9629; e_trg = 0.9394;}
              if (e_pt > 30.0)                 { e_trg_mc = 0.9609; e_trg = 0.9643;}
            } else if (e_eta >= 0.8 && e_eta < 1.479) {
              if (e_pt <= 15.0)                { e_trg_mc = 0.8268; e_trg = 0.7356;}
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.9513; e_trg = 0.9177;}
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9844; e_trg = 0.9515;}
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9776; e_trg = 0.9674;}
              if (e_pt > 30.0)                 { e_trg_mc = 0.9800; e_trg = 0.9778;}
            } else {
              if (e_pt <= 15.0)                { e_trg_mc = 0.7596; e_trg = 0.7010;} 
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.9240; e_trg = 0.8500;}
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9632; e_trg = 0.9323;}
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9803; e_trg = 0.9286;}
              if (e_pt > 30.0)                 { e_trg_mc = 0.9850; e_trg = 0.9737;}
            }
          }
          if (era_ == era::data_2012_moriond) {
            if (m_eta < 0.8) {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9870; m_trg = 0.9713; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9858; m_trg = 0.9706; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9812; m_trg = 0.9749; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9852; m_trg = 0.9711; }
              if (m_pt > 30.0 && m_pt <= 35.0) { m_trg_mc = 0.9826; m_trg = 0.9758; }
              if (m_pt > 35.0)                 { m_trg_mc = 0.9692; m_trg = 0.9683; }
            } else if (m_eta >= 0.8 && m_eta < 1.2) {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9648; m_trg = 0.9399; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9441; m_trg = 0.9284; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9821; m_trg = 0.9423; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9614; m_trg = 0.9439; }
              if (m_pt > 30.0 && m_pt <= 35.0) { m_trg_mc = 0.9504; m_trg = 0.9314; }
              if (m_pt > 35.0)                 { m_trg_mc = 0.9707; m_trg = 0.9345; }
            } else if (m_eta >= 1.2 && m_eta < 1.6) {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9342; m_trg = 0.9299; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9503; m_trg = 0.9306; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9672; m_trg = 0.9375; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9523; m_trg = 0.9222; }
              if (m_pt > 30.0 && m_pt <= 35.0) { m_trg_mc = 0.9191; m_trg = 0.9152; }
              if (m_pt > 35.0)                 { m_trg_mc = 0.9467; m_trg = 0.9098; }
            } else {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9413; m_trg = 0.8614; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9637; m_trg = 0.8921; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9657; m_trg = 0.9114; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9240; m_trg = 0.8909; }
              if (m_pt > 30.0 && m_pt <= 35.0) { m_trg_mc = 0.9566; m_trg = 0.9019; }
              if (m_pt > 35.0)                 { m_trg_mc = 0.9665; m_trg = 0.9003; }
            }
            if (e_eta < 0.8) {
              if (e_pt <= 15.0)                { e_trg_mc = 0.7574; e_trg = 0.7217; }
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.8899; e_trg = 0.8758; }
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9412; e_trg = 0.9145; }
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9601; e_trg = 0.9383; }
              if (e_pt > 30.0 && e_pt <= 35.0) { e_trg_mc = 0.9448; e_trg = 0.9528; }
              if (e_pt > 35.0)                 { e_trg_mc = 0.9624; e_trg = 0.9690; }
            } else if (e_eta >= 0.8 && e_eta < 1.479) {
              if (e_pt <= 15.0)                { e_trg_mc = 0.8198; e_trg = 0.7262; }
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.9343; e_trg = 0.9061; }
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9745; e_trg = 0.9455; }
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9762; e_trg = 0.9681; }
              if (e_pt > 30.0 && e_pt <= 35.0) { e_trg_mc = 0.9749; e_trg = 0.9652; }
              if (e_pt > 35.0)                 { e_trg_mc = 0.9763; e_trg = 0.9811; }
            } else {
              if (e_pt <= 15.0)                { e_trg_mc = 0.7660; e_trg = 0.7093; }
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.9126; e_trg = 0.8475; }
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9617; e_trg = 0.9354; }
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9765; e_trg = 0.9383; }
              if (e_pt > 30.0 && e_pt <= 35.0) { e_trg_mc = 0.9873; e_trg = 0.9693; }
              if (e_pt > 35.0)                 { e_trg_mc = 0.9787; e_trg = 0.9777; }
            }
          }
          if (era_ == era::data_2012_donly) {
            if (m_eta < 0.8) {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9856; m_trg = 0.9778; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9851; m_trg = 0.9768; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9797; m_trg = 0.9756; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9830; m_trg = 0.9770; }
              if (m_pt > 30.0 && m_pt <= 35.0) { m_trg_mc = 0.9827; m_trg = 0.9681; }
              if (m_pt > 35.0)                 { m_trg_mc = 0.9690; m_trg = 0.9676; }
            } else if (m_eta >= 0.8 && m_eta < 1.2) {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9630; m_trg = 0.9386; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9405; m_trg = 0.9325; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9758; m_trg = 0.9359; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9583; m_trg = 0.9400; }
              if (m_pt > 30.0 && m_pt <= 35.0) { m_trg_mc = 0.9501; m_trg = 0.9234; }
              if (m_pt > 35.0)                 { m_trg_mc = 0.9706; m_trg = 0.9399; }
            } else if (m_eta >= 1.2 && m_eta < 1.6) {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9320; m_trg = 0.9337; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9515; m_trg = 0.9396; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9658; m_trg = 0.9458; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9443; m_trg = 0.9348; }
              if (m_pt > 30.0 && m_pt <= 35.0) { m_trg_mc = 0.9269; m_trg = 0.9151; }
              if (m_pt > 35.0)                 { m_trg_mc = 0.9396; m_trg = 0.9123; }
            } else {
              if (m_pt <= 15.0)                { m_trg_mc = 0.9398; m_trg = 0.8320; }
              if (m_pt > 15.0 && m_pt <= 20.0) { m_trg_mc = 0.9611; m_trg = 0.8911; }
              if (m_pt > 20.0 && m_pt <= 25.0) { m_trg_mc = 0.9633; m_trg = 0.8998; }
              if (m_pt > 25.0 && m_pt <= 30.0) { m_trg_mc = 0.9195; m_trg = 0.8917; }
              if (m_pt > 30.0 && m_pt <= 35.0) { m_trg_mc = 0.9512; m_trg = 0.9156; }
              if (m_pt > 35.0)                 { m_trg_mc = 0.9540; m_trg = 0.8890; }
            }
            if (e_eta < 0.8) {
              if (e_pt <= 15.0)                { e_trg_mc = 0.7338; e_trg = 0.6700; }
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.8780; e_trg = 0.8661; }
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9347; e_trg = 0.9107; }
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9583; e_trg = 0.9373; }
              if (e_pt > 30.0 && e_pt <= 35.0) { e_trg_mc = 0.9413; e_trg = 0.9610; }
              if (e_pt > 35.0)                 { e_trg_mc = 0.9613; e_trg = 0.9723; }
            } else if (e_eta >= 0.8 && e_eta < 1.479) {
              if (e_pt <= 15.0)                { e_trg_mc = 0.8111; e_trg = 0.7176; }
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.9256; e_trg = 0.8927; }
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9695; e_trg = 0.9370; }
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9754; e_trg = 0.9724; }
              if (e_pt > 30.0 && e_pt <= 35.0) { e_trg_mc = 0.9752; e_trg = 0.9751; }
              if (e_pt > 35.0)                 { e_trg_mc = 0.9750; e_trg = 0.9792; }
            } else {
              if (e_pt <= 15.0)                { e_trg_mc = 0.7702; e_trg = 0.7167; }
              if (e_pt > 15.0 && e_pt <= 20.0) { e_trg_mc = 0.9057; e_trg = 0.8516; }
              if (e_pt > 20.0 && e_pt <= 25.0) { e_trg_mc = 0.9569; e_trg = 0.9368; }
              if (e_pt > 25.0 && e_pt <= 30.0) { e_trg_mc = 0.9790; e_trg = 0.9595; }
              if (e_pt > 30.0 && e_pt <= 35.0) { e_trg_mc = 0.9865; e_trg = 0.9792; }
              if (e_pt > 35.0)                 { e_trg_mc = 0.9777; e_trg = 0.9813; }
            }
          }
        } else if (mc_ == mc::fall11_42X) {
          if (m_eta < 1.5) {
            if (m_pt <= 15.0) m_trg = 1.01;
            if (m_pt > 15.0 && m_pt <= 20.0) m_trg = 0.99;
            if (m_pt > 20.0 && m_pt <= 30.0) m_trg = 0.99;
            if (m_pt > 30.0) m_trg = 0.992;
          } else {
            if (m_pt <= 15.0) m_trg = 1.03;
            if (m_pt > 15.0 && m_pt <= 20.0) m_trg = 1.07;
            if (m_pt > 20.0 && m_pt <= 30.0) m_trg = 1.04;
            if (m_pt > 30.0) m_trg = 1.06;
          }
          if (e_eta < 1.479) {
            if (e_pt <= 15.0) e_trg = 0.98;
            if (e_pt > 15.0 && e_pt <= 20.0) e_trg = 1.00;
            if (e_pt > 20.0 && e_pt <= 30.0) e_trg = 1.001;
            if (e_pt > 30.0) e_trg = 1.003;
          } else {
            if (e_pt <= 15.0) e_trg = 0.97;
            if (e_pt > 15.0 && e_pt <= 20.0) e_trg = 1.05;
            if (e_pt > 20.0 && e_pt <= 30.0) e_trg = 1.00;
            if (e_pt > 30.0) e_trg = 1.008;
          }
        }
        if (trg_applied_in_mc_) {
          m_trg = m_trg / m_trg_mc;
          e_trg = e_trg / e_trg_mc;
        }
        weight *= (e_trg * m_trg);
        event->Add("trigweight_1", e_trg);
        event->Add("trigweight_2", m_trg);
      }
    }

    if (do_idiso_weights_ || do_id_weights_) {
      if (channel_ == channel::et) {
        Electron const* elec = dynamic_cast<Electron const*>(dilepton[0]->GetCandidate("lepton1"));
        double pt = elec->pt();
        double sc_eta = fabs(elec->sc_eta());
        double ele_id = 1.0;
        double ele_iso = 1.0;
        if (mc_ == mc::summer12_53X) {
          if (era_ == era::data_2012_ichep) {
            if (pt > 24.0 && pt <= 30.0 && sc_eta < 1.479)  { ele_id = 0.9189; ele_iso = 0.9643; }
            if (pt > 24.0 && pt <= 30.0 && sc_eta >= 1.479) { ele_id = 0.8689; ele_iso = 0.9747; }
            if (pt > 30.0 && sc_eta < 1.479)                { ele_id = 0.9593; ele_iso = 0.9877; }
            if (pt > 30.0 && sc_eta >= 1.479)               { ele_id = 0.9223; ele_iso = 0.9938; }  
          }
          if (era_ == era::data_2012_hcp) {
            if (pt > 24.0 && pt <= 30.0 && sc_eta < 1.479)  { ele_id = 0.9130; ele_iso = 0.9602; }
            if (pt > 24.0 && pt <= 30.0 && sc_eta >= 1.479) { ele_id = 0.8509; ele_iso = 0.9661; }
            if (pt > 30.0 && sc_eta < 1.479)                { ele_id = 0.9567; ele_iso = 0.9858; }
            if (pt > 30.0 && sc_eta >= 1.479)               { ele_id = 0.9239; ele_iso = 0.9942; }  
          }
          if (era_ == era::data_2012_moriond || era_ == era::data_2012_donly) {
            if (pt > 24.0 && pt <= 30.0 && sc_eta < 1.479)  { ele_id = 0.9100; ele_iso = 0.9468; }
            if (pt > 24.0 && pt <= 30.0 && sc_eta >= 1.479) { ele_id = 0.8244; ele_iso = 0.9586; }
            if (pt > 30.0 && sc_eta < 1.479)                { ele_id = 0.9493; ele_iso = 0.9820; }
            if (pt > 30.0 && sc_eta >= 1.479)               { ele_id = 0.9260; ele_iso = 0.9948; }  
          }
        } else if (mc_ == mc::fall11_42X) {    
          if (pt > 20.0 && pt <= 30.0 && sc_eta < 1.479)  { ele_id = 0.9590; ele_iso = 0.9907; }
          if (pt > 20.0 && pt <= 30.0 && sc_eta >= 1.479) { ele_id = 0.9462; ele_iso = 0.9875; }
          if (pt > 30.0 && sc_eta < 1.479)                { ele_id = 0.9826; ele_iso = 0.9845; }
          if (pt > 30.0 && sc_eta >= 1.479)               { ele_id = 0.9689; ele_iso = 0.9971; }
        }
        if (do_id_weights_) ele_iso = 1.0;
        weight *= (ele_id * ele_iso);
        event->Add("idweight_1", ele_id);
        event->Add("idweight_2", double(1.0));
        event->Add("isoweight_1", ele_iso);
        event->Add("isoweight_2", double(1.0));
      } else if (channel_ == channel::mt) {
        Muon const* muon = dynamic_cast<Muon const*>(dilepton[0]->GetCandidate("lepton1"));
        double pt = muon->pt();
        double m_eta = fabs(muon->eta());
        double mu_id = 1.0;
        double mu_iso = 1.0;
        if (mc_ == mc::summer12_53X) {
          if (era_ == era::data_2012_ichep) {
            if (pt > 20.0 && pt <= 30.0 && m_eta < 0.8)                   { mu_id = 0.9884; mu_iso = 0.9753; }
            if (pt > 20.0 && pt <= 30.0 && m_eta >= 0.8 && m_eta < 1.2)   { mu_id = 0.9860; mu_iso = 0.9851; }
            if (pt > 20.0 && pt <= 30.0 && m_eta >= 1.2)                  { mu_id = 0.9920; mu_iso = 0.9964; }
            if (pt > 30.0 && m_eta < 0.8)                                 { mu_id = 0.9879; mu_iso = 0.9894; }
            if (pt > 30.0 && m_eta >= 0.8 && m_eta < 1.2)                 { mu_id = 0.9827; mu_iso = 0.9880; }
            if (pt > 30.0 && m_eta >= 1.2)                                { mu_id = 0.9919; mu_iso = 1.0005; }
          }
          if (era_ == era::data_2012_hcp) {
            if (pt > 20.0 && pt <= 30.0 && m_eta < 0.8)                   { mu_id = 0.9870; mu_iso = 0.9715; }
            if (pt > 20.0 && pt <= 30.0 && m_eta >= 0.8 && m_eta < 1.2)   { mu_id = 0.9837; mu_iso = 0.9826; }
            if (pt > 20.0 && pt <= 30.0 && m_eta >= 1.2)                  { mu_id = 0.9914; mu_iso = 0.9960; }
            if (pt > 30.0 && m_eta < 0.8)                                 { mu_id = 0.9871; mu_iso = 0.9880; }
            if (pt > 30.0 && m_eta >= 0.8 && m_eta < 1.2)                 { mu_id = 0.9817; mu_iso = 0.9870; }
            if (pt > 30.0 && m_eta >= 1.2)                                { mu_id = 1.0018; mu_iso = 1.0008; }
          }
          if (era_ == era::data_2012_moriond || era_ == era::data_2012_donly) {
            if (pt > 20.0 && pt <= 30.0 && m_eta < 0.8)                   { mu_id = 0.9853; mu_iso = 0.9685; }
            if (pt > 20.0 && pt <= 30.0 && m_eta >= 0.8 && m_eta < 1.2)   { mu_id = 0.9818; mu_iso = 0.9808; }
            if (pt > 20.0 && pt <= 30.0 && m_eta >= 1.2)                  { mu_id = 0.9899; mu_iso = 0.9972; }
            if (pt > 30.0 && m_eta < 0.8)                                 { mu_id = 0.9857; mu_iso = 0.9872; }
            if (pt > 30.0 && m_eta >= 0.8 && m_eta < 1.2)                 { mu_id = 0.9805; mu_iso = 0.9924; }
            if (pt > 30.0 && m_eta >= 1.2)                                { mu_id = 0.9900; mu_iso = 1.0012; }
          }
        } else if (mc_ == mc::fall11_42X) {
          if (pt > 17.0 && pt <= 20.0 && m_eta < 0.8)                   { mu_id = 0.9963; mu_iso = 0.9910; }
          if (pt > 17.0 && pt <= 20.0 && m_eta >= 0.8 && m_eta < 1.2)   { mu_id = 0.9846; mu_iso = 0.9643; }
          if (pt > 17.0 && pt <= 20.0 && m_eta >= 1.2)                  { mu_id = 0.9830; mu_iso = 0.9504; }
          if (pt > 20.0 && pt <= 30.0 && m_eta < 0.8)                   { mu_id = 0.9962; mu_iso = 1.0011; }
          if (pt > 20.0 && pt <= 30.0 && m_eta >= 0.8 && m_eta < 1.2)   { mu_id = 0.9904; mu_iso = 0.9834; }
          if (pt > 20.0 && pt <= 30.0 && m_eta >= 1.2)                  { mu_id = 0.9828; mu_iso = 0.9975; }
          if (pt > 30.0 && m_eta < 0.8)                                 { mu_id = 0.9977; mu_iso = 0.9895; }
          if (pt > 30.0 && m_eta >= 0.8 && m_eta < 1.2)                 { mu_id = 0.9893; mu_iso = 0.9936; }
          if (pt > 30.0 && m_eta >= 1.2)                                { mu_id = 0.9829; mu_iso = 0.9960; }
        }
        if (do_id_weights_) mu_iso = 1.0;
        weight *= (mu_id * mu_iso);
        event->Add("idweight_1", mu_id);
        event->Add("idweight_2", double(1.0));
        event->Add("isoweight_1", mu_iso);
        event->Add("isoweight_2", double(1.0));
      } else if (channel_ == channel::em) {
        Electron const* elec = dynamic_cast<Electron const*>(dilepton[0]->GetCandidate("lepton1"));
        Muon const* muon = dynamic_cast<Muon const*>(dilepton[0]->GetCandidate("lepton2"));
        double e_pt = elec->pt();
        double e_eta = fabs(elec->sc_eta());
        double m_pt = muon->pt();
        double m_eta = fabs(muon->eta());
        double m_idiso = 1.0;
        double e_idiso = 1.0;
        if (mc_ == mc::summer12_53X) {
          if (era_ == era::data_2012_ichep || era_ == era::data_2012_hcp) {
            if (m_eta < 0.8) {
              if (m_pt <= 15.0)                 m_idiso = 0.9845;
              if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 0.9644;
              if (m_pt > 20.0)                  m_idiso = 0.9884;
            } else if (m_eta >= 0.8 && m_eta < 1.5) {
              if (m_pt <= 15.0)                 m_idiso = 0.9869;
              if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 0.9800;
              if (m_pt > 20.0)                  m_idiso = 0.9884;
            } else {
              if (m_pt <= 15.0)                 m_idiso = 0.9927;
              if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 0.9961;
              if (m_pt > 20.0)                  m_idiso = 0.9941; 
            }
            if (e_eta < 0.8) {
              if (e_pt <= 15.0)                 e_idiso = 0.7893;
              if (e_pt > 15.0 && e_pt <= 20.0)  e_idiso = 0.8506;
              if (e_pt > 20.0)                  e_idiso = 0.9534;
            } else if (e_eta >= 0.8 && e_eta < 1.479) {
              if (e_pt <= 15.0)                 e_idiso = 0.7952;
              if (e_pt > 15.0 && e_pt <= 20.0)  e_idiso = 0.8661;
              if (e_pt > 20.0)                  e_idiso = 0.9481;
            } else {
              if (e_pt <= 15.0)                 e_idiso = 0.6519;
              if (e_pt > 15.0 && e_pt <= 20.0)  e_idiso = 0.7816;
              if (e_pt > 20.0)                  e_idiso = 0.9378;
            }
          } else if (era_ == era::data_2012_moriond) {
            if (m_eta < 0.8) {
              if (m_pt <= 15.0)                 m_idiso = 0.9811;
              if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 0.9556;
              if (m_pt > 20.0 && m_pt <= 25.0)  m_idiso = 0.9676;
              if (m_pt > 25.0 && m_pt <= 30.0)  m_idiso = 0.9691;
              if (m_pt > 30.0 && m_pt <= 35.0)  m_idiso = 0.9746;
              if (m_pt > 35.0)                  m_idiso = 0.9987;
            } else if (m_eta >= 0.8 && m_eta < 1.2) {
              if (m_pt <= 15.0)                 m_idiso = 0.9689;
              if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 0.9635;
              if (m_pt > 20.0 && m_pt <= 25.0)  m_idiso = 0.9785;
              if (m_pt > 25.0 && m_pt <= 30.0)  m_idiso = 0.9785;
              if (m_pt > 30.0 && m_pt <= 35.0)  m_idiso = 0.9797;
              if (m_pt > 35.0)                  m_idiso = 0.9841;
            } else if (m_eta >= 1.2 && m_eta < 1.6) {
              if (m_pt <= 15.0)                 m_idiso = 0.9757;
              if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 0.9806;
              if (m_pt > 20.0 && m_pt <= 25.0)  m_idiso = 0.9883;
              if (m_pt > 25.0 && m_pt <= 30.0)  m_idiso = 0.9909;
              if (m_pt > 30.0 && m_pt <= 35.0)  m_idiso = 0.9813;
              if (m_pt > 35.0)                  m_idiso = 0.9919;
            } else {
              if (m_pt <= 15.0)                 m_idiso = 1.0069;
              if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 1.0078;
              if (m_pt > 20.0 && m_pt <= 25.0)  m_idiso = 1.0031;
              if (m_pt > 25.0 && m_pt <= 30.0)  m_idiso = 0.9991;
              if (m_pt > 30.0 && m_pt <= 35.0)  m_idiso = 0.9935;
              if (m_pt > 35.0)                  m_idiso = 0.9939;
            }
            if (e_eta < 0.8) {
              if (e_pt <= 15.0)                 e_idiso = 0.7570;
              if (e_pt > 15.0 && e_pt <= 20.0)  e_idiso = 0.8437;
              if (e_pt > 20.0 && e_pt <= 25.0)  e_idiso = 0.8817;
              if (e_pt > 25.0 && e_pt <= 30.0)  e_idiso = 0.9069;
              if (e_pt > 30.0 && e_pt <= 35.0)  e_idiso = 0.9301;
              if (e_pt > 35.0)                  e_idiso = 0.9533;
            } else if (e_eta >= 0.8 && e_eta < 1.479) {
              if (e_pt <= 15.0)                 e_idiso = 0.7807;
              if (e_pt > 15.0 && e_pt <= 20.0)  e_idiso = 0.8447;
              if (e_pt > 20.0 && e_pt <= 25.0)  e_idiso = 0.8492;
              if (e_pt > 25.0 && e_pt <= 30.0)  e_idiso = 0.8896;
              if (e_pt > 30.0 && e_pt <= 35.0)  e_idiso = 0.9230;
              if (e_pt > 35.0)                  e_idiso = 0.9496;
            } else {
              if (e_pt <= 15.0)                 e_idiso = 0.6276;
              if (e_pt > 15.0 && e_pt <= 20.0)  e_idiso = 0.7812;
              if (e_pt > 20.0 && e_pt <= 25.0)  e_idiso = 0.8057;
              if (e_pt > 25.0 && e_pt <= 30.0)  e_idiso = 1.0225;
              if (e_pt > 30.0 && e_pt <= 35.0)  e_idiso = 0.8887;
              if (e_pt > 35.0)                  e_idiso = 0.9389;
            }
          } else if (era_ == era::data_2012_donly) {
            if (m_eta < 0.8) {
              if (m_pt <= 15.0)                 m_idiso = 0.9775;
              if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 0.9436;
              if (m_pt > 20.0 && m_pt <= 25.0)  m_idiso = 0.9592;
              if (m_pt > 25.0 && m_pt <= 30.0)  m_idiso = 0.9631;
              if (m_pt > 30.0 && m_pt <= 35.0)  m_idiso = 0.9703;
              if (m_pt > 35.0)                  m_idiso = 0.9810;
            } else if (m_eta >= 0.8 && m_eta < 1.2) {
              if (m_pt <= 15.0)                 m_idiso = 0.9611;
              if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 0.9485;
              if (m_pt > 20.0 && m_pt <= 25.0)  m_idiso = 0.9733;
              if (m_pt > 25.0 && m_pt <= 30.0)  m_idiso = 0.9752;
              if (m_pt > 30.0 && m_pt <= 35.0)  m_idiso = 0.9710;
              if (m_pt > 35.0)                  m_idiso = 0.9794;
            } else if (m_eta >= 1.2 && m_eta < 1.6) {
              if (m_pt <= 15.0)                 m_idiso = 0.9770;
              if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 0.9787;
              if (m_pt > 20.0 && m_pt <= 25.0)  m_idiso = 0.9865;
              if (m_pt > 25.0 && m_pt <= 30.0)  m_idiso = 0.9880;
              if (m_pt > 30.0 && m_pt <= 35.0)  m_idiso = 0.9914;
              if (m_pt > 35.0)                  m_idiso = 0.9912;
            } else {
              if (m_pt <= 15.0)                 m_idiso = 1.0095;
              if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 1.0103;
              if (m_pt > 20.0 && m_pt <= 25.0)  m_idiso = 1.0100;
              if (m_pt > 25.0 && m_pt <= 30.0)  m_idiso = 1.0018;
              if (m_pt > 30.0 && m_pt <= 35.0)  m_idiso = 1.0033;
              if (m_pt > 35.0)                  m_idiso = 0.9939;
            }
            if (e_eta < 0.8) {
              if (e_pt <= 15.0)                 e_idiso = 0.6794;
              if (e_pt > 15.0 && e_pt <= 20.0)  e_idiso = 0.8141;
              if (e_pt > 20.0 && e_pt <= 25.0)  e_idiso = 0.8633;
              if (e_pt > 25.0 && e_pt <= 30.0)  e_idiso = 0.8950;
              if (e_pt > 30.0 && e_pt <= 35.0)  e_idiso = 0.9209;
              if (e_pt > 35.0)                  e_idiso = 0.9473;
            } else if (e_eta >= 0.8 && e_eta < 1.479) {
              if (e_pt <= 15.0)                 e_idiso = 0.7353;
              if (e_pt > 15.0 && e_pt <= 20.0)  e_idiso = 0.8093;
              if (e_pt > 20.0 && e_pt <= 25.0)  e_idiso = 0.8239;
              if (e_pt > 25.0 && e_pt <= 30.0)  e_idiso = 0.8775;
              if (e_pt > 30.0 && e_pt <= 35.0)  e_idiso = 0.9129;
              if (e_pt > 35.0)                  e_idiso = 0.9417;
            } else {
              if (e_pt <= 15.0)                 e_idiso = 0.5834;
              if (e_pt > 15.0 && e_pt <= 20.0)  e_idiso = 0.7499;
              if (e_pt > 20.0 && e_pt <= 25.0)  e_idiso = 0.7744;
              if (e_pt > 25.0 && e_pt <= 30.0)  e_idiso = 0.8368;
              if (e_pt > 30.0 && e_pt <= 35.0)  e_idiso = 0.8704;
              if (e_pt > 35.0)                  e_idiso = 0.9308;
            }
          }
        } else {
          if (m_eta < 1.5) {
            if (m_pt <= 15.0)                 m_idiso = 0.9895;
            if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 1.0168;
            if (m_pt > 20.0)                  m_idiso = 1.0061;
          } else {
            if (m_pt <= 15.0)                 m_idiso = 1.0303;
            if (m_pt > 15.0 && m_pt <= 20.0)  m_idiso = 1.0247;
            if (m_pt > 20.0)                  m_idiso = 1.0144;
          }
          if (e_eta < 1.479) {
            if (e_pt <= 15.0)                 e_idiso = 1.0396;
            if (e_pt > 15.0 && e_pt <= 20.0)  e_idiso = 0.9622;
            if (e_pt > 20.0)                  e_idiso = 0.9849;
          } else {
            if (e_pt <= 15.0)                 e_idiso = 0.9758;
            if (e_pt > 15.0 && e_pt <= 20.0)  e_idiso = 1.1483;
            if (e_pt > 20.0)                  e_idiso = 1.0117;
          }
        }
        // if (do_id_weights_) mu_iso = 1.0;
        weight *= (e_idiso * m_idiso);
        event->Add("idweight_1", e_idiso);
        event->Add("idweight_2", m_idiso);
        event->Add("isoweight_1", double(1.0));
        event->Add("isoweight_2", double(1.0));
      }
    }

    eventInfo->set_weight("lepton", weight);

    if (do_emu_e_fakerates_) {
      Electron const* elec = dynamic_cast<Electron const*>(dilepton[0]->GetCandidate("lepton1"));
      double elefopt = (elec->pt() < 35) ? elec->pt() : 34.99;
      double eleEta = elec->eta();
      if (era_ == era::data_2012_donly || era_ == era::data_2012_moriond) eleEta = fabs(eleEta);
      int eleptbin = ElectronFakeRateHist_PtEta->GetXaxis()->FindFixBin(elefopt);
      int eleetabin = ElectronFakeRateHist_PtEta->GetYaxis()->FindFixBin(eleEta);    
      double eleprob = ElectronFakeRateHist_PtEta->GetBinContent(eleptbin,eleetabin);
      double elefakerate = eleprob/(1.0 - eleprob);
      //double elefakerate_errlow = ElectronFakeRateHist_PtEta->GetError(elefopt,fabs(elec->eta()),mithep::TH2DAsymErr::kStatErrLow)/pow((1-ElectronFakeRateHist_PtEta->GetError(elefopt,fabs(elec->eta()),mithep::TH2DAsymErr::kStatErrLow)),2);
      //double elefakerate_errhigh = ElectronFakeRateHist_PtEta->GetError(elefopt,fabs(elec->eta()),mithep::TH2DAsymErr::kStatErrHigh)/pow((1-ElectronFakeRateHist_PtEta->GetError(elefopt,fabs(elec->eta()),mithep::TH2DAsymErr::kStatErrHigh)),2);
      eventInfo->set_weight("emu_e_fakerate", elefakerate);
    }

    if (do_emu_m_fakerates_) {
      Muon const* muon = dynamic_cast<Muon const*>(dilepton[0]->GetCandidate("lepton2"));
      Double_t mufopt = (muon->pt() < 35) ? muon->pt() : 34.99;
      double muEta = muon->eta();
      if (era_ == era::data_2012_donly || era_ == era::data_2012_moriond) muEta = fabs(muEta);
      int muptbin = MuonFakeRateHist_PtEta->GetXaxis()->FindFixBin(mufopt);
      int muetabin = MuonFakeRateHist_PtEta->GetYaxis()->FindFixBin(muEta);    
      double muprob = MuonFakeRateHist_PtEta->GetBinContent(muptbin,muetabin);
      double mufakerate = muprob/(1.0 - muprob);
      //double mufakerate_errlow = MuonFakeRateHist_PtEta->GetError(mufopt,fabs(muon->eta()),mithep::TH2DAsymErr::kStatErrLow)/pow((1-MuonFakeRateHist_PtEta->GetError(mufopt,fabs(muon->eta()),mithep::TH2DAsymErr::kStatErrLow)),2);
      //double mufakerate_errhigh = MuonFakeRateHist_PtEta->GetError(mufopt,fabs(muon->eta()),mithep::TH2DAsymErr::kStatErrHigh)/pow((1-MuonFakeRateHist_PtEta->GetError(mufopt,fabs(muon->eta()),mithep::TH2DAsymErr::kStatErrHigh)),2);
      eventInfo->set_weight("emu_m_fakerate", mufakerate);
    }

    if (do_etau_fakerate_) {
      std::vector<GenParticle *> parts = event->GetPtrVec<GenParticle>("genParticles");
      ic::erase_if(parts, !(boost::bind(&GenParticle::status, _1) == 3));
      ic::erase_if(parts, ! ((boost::bind(&GenParticle::pdgid, _1) == 11)||(boost::bind(&GenParticle::pdgid, _1) == -11)) );
      ic::erase_if(parts, ! (boost::bind(MinPtMaxEta, _1, 8.0, 2.6)));
      std::vector<Candidate *> tau_cand;
      tau_cand.push_back(dilepton[0]->GetCandidate("lepton2"));
      Tau const* tau = dynamic_cast<Tau const*>(dilepton[0]->GetCandidate("lepton2"));
      std::vector<std::pair<Candidate*, GenParticle*> > matches = MatchByDR(tau_cand, parts, 0.5, true, true);
      // Mode 0 Barrel: 0.87 +/- 0.04
      // Mode 0 Endcap: 0.40 +/- 0.20
      // Mode 1 Barrel: 1.19 +/- 0.06
      // Mode 1 Endcap: 0.72 +/ 0.17
      if (matches.size() > 0) {
        if (mc_ == mc::fall11_42X) {
          if (fabs(tau_cand[0]->eta()) < 1.5) {
            if (tau->decay_mode() == 0) eventInfo->set_weight("etau_fakerate", 0.87);
            if (tau->decay_mode() == 1) eventInfo->set_weight("etau_fakerate", 1.19);
          } else {
            if (tau->decay_mode() == 0) eventInfo->set_weight("etau_fakerate", 0.40);
            if (tau->decay_mode() == 1) eventInfo->set_weight("etau_fakerate", 0.72);
          }
        } else {
          if (era_ == era::data_2012_ichep || era_ == era::data_2012_hcp) {
            if (fabs(tau_cand[0]->eta()) < 1.5) {
              if (tau->decay_mode() == 0) eventInfo->set_weight("etau_fakerate", 0.85);
              if (tau->decay_mode() == 1) {
                eventInfo->set_weight("etau_fakerate", 1.64);
                event->Add("mass_scale", double(1.015));
              }
            } else {
              if (tau->decay_mode() == 0) eventInfo->set_weight("etau_fakerate", 1.85);
              if (tau->decay_mode() == 1) {
                eventInfo->set_weight("etau_fakerate", 0.28);
                event->Add("mass_scale", double(1.015));
              }
            } 
          }
          if (era_ == era::data_2012_moriond || era_ == era::data_2012_donly) {
            if (fabs(tau_cand[0]->eta()) < 1.5) {
              if (tau->decay_mode() == 0) eventInfo->set_weight("etau_fakerate", 0.85);
              if (tau->decay_mode() == 1) eventInfo->set_weight("etau_fakerate", 1.52);
            } else {
              event->Add("mass_scale", double(1.015));
              if (tau->decay_mode() == 0) eventInfo->set_weight("etau_fakerate", 0.94);
              if (tau->decay_mode() == 1) eventInfo->set_weight("etau_fakerate", 0.32);
            } 
          }
        }
      }
    }

    if (do_mtau_fakerate_) {
      std::vector<GenParticle *> parts = event->GetPtrVec<GenParticle>("genParticles");
      ic::erase_if(parts, !(boost::bind(&GenParticle::status, _1) == 3));
      ic::erase_if(parts, ! ((boost::bind(&GenParticle::pdgid, _1) == 13)||(boost::bind(&GenParticle::pdgid, _1) == -13)) );
      ic::erase_if(parts, ! (boost::bind(MinPtMaxEta, _1, 8.0, 2.6)));
      std::vector<Candidate *> tau_cand;
      tau_cand.push_back(dilepton[0]->GetCandidate("lepton2"));
      std::vector<std::pair<Candidate*, GenParticle*> > matches = MatchByDR(tau_cand, parts, 0.5, true, true);
      // Constant scaling of 1.25 in 2012, nothing in 2011
      if (matches.size() > 0) {
        if (mc_ == mc::fall11_42X) {

        } else {
          if (era_ == era::data_2012_ichep || era_ == era::data_2012_hcp) {
            eventInfo->set_weight("mtau_fakerate", 1.00);
          }
          if (era_ == era::data_2012_moriond || era_ == era::data_2012_donly) {
            eventInfo->set_weight("mtau_fakerate", 1.00);
          }
        }
      }
    }

    if (do_w_soup_) {
      std::vector<GenParticle*> const& parts = event->GetPtrVec<GenParticle>("genParticles");
      bool count_jets = false;
      unsigned partons = 0;
      for (unsigned i = 0; i < parts.size(); ++i) {
        if (parts[i]->status() != 3) continue;
        unsigned id = abs(parts[i]->pdgid());
        if (count_jets) { 
          if (id == 1 || id == 2 || id == 3 || id == 4 || id == 5 || id == 6 || id == 21) partons++;
        }
        if (id == 24) count_jets = true; 
      }
      if (partons > 4) {
        std::cerr << "Error making soup, event has " << partons << " partons!" << std::endl;
        throw;
      }
      if (partons == 1) eventInfo->set_weight("wsoup", w1_);
      if (partons == 2) eventInfo->set_weight("wsoup", w2_);
      if (partons == 3) eventInfo->set_weight("wsoup", w3_);
      if (partons == 4) eventInfo->set_weight("wsoup", w4_);
    }

    if (do_dy_soup_) {
      std::vector<GenParticle*> const& parts = event->GetPtrVec<GenParticle>("genParticles");
      bool count_jets = false;
      unsigned partons = 0;
      for (unsigned i = 0; i < parts.size(); ++i) {
        // std::cout << i << "\t" << parts[i]->status() << "\t" << parts[i]->pdgid() << "\t" << parts[i]->vector() << std::endl;
        if (parts[i]->status() != 3) continue;
        unsigned id = abs(parts[i]->pdgid());
        if (count_jets) { 
          if (id == 1 || id == 2 || id == 3 || id == 4 || id == 5 || id == 6 || id == 21) partons++;
        }
        if (id == 23) count_jets = true; 
      }
      if (partons > 4) {
        std::cerr << "Error making soup, event has " << partons << " partons!" << std::endl;
        throw;
      }
      if (partons == 1) eventInfo->set_weight("dysoup", zw1_);
      if (partons == 2) eventInfo->set_weight("dysoup", zw2_);
      if (partons == 3) eventInfo->set_weight("dysoup", zw3_);
      if (partons == 4) eventInfo->set_weight("dysoup", zw4_);
    }

    return 0;
  }

  int HTTWeights::PostAnalysis() {
    return 0;
  }

  void HTTWeights::PrintInfo() {
    ;
  }

  void HTTWeights::SetWTargetFractions(double f0, double f1, double f2, double f3, double f4) {
    f0_ = f0;
    f1_ = f1;
    f2_ = f2;
    f3_ = f3;
    f4_ = f4;

  }
  void HTTWeights::SetWInputYields(double n_inc, double n1, double n2, double n3, double n4) {
    n_inc_ = n_inc;
    n1_ = n1;
    n2_ = n2;
    n3_ = n3;
    n4_ = n4;
  }

  void HTTWeights::SetDYTargetFractions(double zf0, double zf1, double zf2, double zf3, double zf4) {
    zf0_ = zf0;
    zf1_ = zf1;
    zf2_ = zf2;
    zf3_ = zf3;
    zf4_ = zf4;

  }
  void HTTWeights::SetDYInputYields(double zn_inc, double zn1, double zn2, double zn3, double zn4) {
    zn_inc_ = zn_inc;
    zn1_ = zn1;
    zn2_ = zn2;
    zn3_ = zn3;
    zn4_ = zn4;
  }

  double HTTWeights::Efficiency(double m, double m0, double sigma, double alpha,
    double n, double norm)
  {
    const double sqrtPiOver2 = 1.2533141373;
    const double sqrt2 = 1.4142135624;
    double sig = fabs((double) sigma);
    double t = (m - m0)/sig;
    if(alpha < 0)
      t = -t;
    double absAlpha = fabs(alpha/sig);
    double a = TMath::Power(n/absAlpha,n)*exp(-0.5*absAlpha*absAlpha);
    double b = absAlpha - n/absAlpha;
    double ApproxErf;
    double arg = absAlpha / sqrt2;
    if (arg > 5.) ApproxErf = 1;
    else if (arg < -5.) ApproxErf = -1;
    else ApproxErf = TMath::Erf(arg);
    double leftArea = (1 + ApproxErf) * sqrtPiOver2;
    double rightArea = ( a * 1/TMath::Power(absAlpha - b,n-1)) / (n - 1);
    double area = leftArea + rightArea;
    if( t <= absAlpha ){
      arg = t / sqrt2;
      if(arg > 5.) ApproxErf = 1;
      else if (arg < -5.) ApproxErf = -1;
      else ApproxErf = TMath::Erf(arg);
      return norm * (1 + ApproxErf) * sqrtPiOver2 / area;
    }
    else{
      return norm * (leftArea + a * (1/TMath::Power(t-b,n-1) -
        1/TMath::Power(absAlpha - b,n-1)) / (1 - n)) / area;
    }
  }
}
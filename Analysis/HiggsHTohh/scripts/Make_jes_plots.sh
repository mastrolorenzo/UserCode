
./bin/PlotCompare -p "ggHTohh300-central:ggHTohh300-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ggHTohhTo2Tau2B300:-1:1:4" -p "ggHTohh300-JESup:ggHTohh300-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVUp:-1:2:2" -p "ggHTohh300-JESdown:ggHTohh300-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ggHTohh300_jes_2jet0tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "TT-central:TT-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:TT:-1:1:4" -p "TT-JESup:TT-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:TT_CMS_scale_j_8TeVUp:-1:2:2" -p "TT-JESdown:TT-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:TT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="TT_jes_2jet0tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "QCD-central:QCD-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:QCD:-1:1:4" -p "QCD-JESup:QCD-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:QCD_CMS_scale_j_8TeVUp:-1:2:2" -p "QCD-JESdown:QCD-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:QCD_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="QCD_jes_2jet0tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "W-central:W-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:W:-1:1:4" -p "W-JESup:W-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:W_CMS_scale_j_8TeVUp:-1:2:2" -p "W-JESdown:W-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:W_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="W_jes_2jet0tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZTT-central:ZTT-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ZTT:-1:1:4" -p "ZTT-JESup:ZTT-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ZTT_CMS_scale_j_8TeVUp:-1:2:2" -p "ZTT-JESdown:ZTT-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ZTT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZTT_jes_2jet0tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZJ-central:ZJ-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ZJ:-1:1:4" -p "ZJ-JESup:ZJ-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ZJ_CMS_scale_j_8TeVUp:-1:2:2" -p "ZJ-JESdown:ZJ-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ZJ_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZJ_jes_2jet0tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZL-central:ZL-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ZL:-1:1:4" -p "ZL-JESup:ZL-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ZL_CMS_scale_j_8TeVUp:-1:2:2" -p "ZL-JESdown:ZL-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:ZL_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZL_jes_2jet0tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "VV-central:VV-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:VV:-1:1:4" -p "VV-JESup:VV-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:VV_CMS_scale_j_8TeVUp:-1:2:2" -p "VV-JESdown:VV-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet0tag:VV_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="VV_jes_2jet0tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ggHTohh300-central:ggHTohh300-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ggHTohhTo2Tau2B300:-1:1:4" -p "ggHTohh300-JESup:ggHTohh300-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVUp:-1:2:2" -p "ggHTohh300-JESdown:ggHTohh300-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ggHTohh300_jes_2jet1tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "TT-central:TT-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:TT:-1:1:4" -p "TT-JESup:TT-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:TT_CMS_scale_j_8TeVUp:-1:2:2" -p "TT-JESdown:TT-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:TT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="TT_jes_2jet1tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "QCD-central:QCD-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:QCD:-1:1:4" -p "QCD-JESup:QCD-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:QCD_CMS_scale_j_8TeVUp:-1:2:2" -p "QCD-JESdown:QCD-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:QCD_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="QCD_jes_2jet1tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "W-central:W-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:W:-1:1:4" -p "W-JESup:W-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:W_CMS_scale_j_8TeVUp:-1:2:2" -p "W-JESdown:W-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:W_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="W_jes_2jet1tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZTT-central:ZTT-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ZTT:-1:1:4" -p "ZTT-JESup:ZTT-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ZTT_CMS_scale_j_8TeVUp:-1:2:2" -p "ZTT-JESdown:ZTT-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ZTT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZTT_jes_2jet1tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZJ-central:ZJ-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ZJ:-1:1:4" -p "ZJ-JESup:ZJ-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ZJ_CMS_scale_j_8TeVUp:-1:2:2" -p "ZJ-JESdown:ZJ-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ZJ_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZJ_jes_2jet1tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZL-central:ZL-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ZL:-1:1:4" -p "ZL-JESup:ZL-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ZL_CMS_scale_j_8TeVUp:-1:2:2" -p "ZL-JESdown:ZL-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:ZL_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZL_jes_2jet1tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "VV-central:VV-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:VV:-1:1:4" -p "VV-JESup:VV-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:VV_CMS_scale_j_8TeVUp:-1:2:2" -p "VV-JESdown:VV-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet1tag:VV_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="VV_jes_2jet1tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ggHTohh300-central:ggHTohh300-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ggHTohhTo2Tau2B300:-1:1:4" -p "ggHTohh300-JESup:ggHTohh300-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVUp:-1:2:2" -p "ggHTohh300-JESdown:ggHTohh300-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ggHTohh300_jes_2jet2tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "TT-central:TT-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:TT:-1:1:4" -p "TT-JESup:TT-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:TT_CMS_scale_j_8TeVUp:-1:2:2" -p "TT-JESdown:TT-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:TT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="TT_jes_2jet2tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "QCD-central:QCD-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:QCD:-1:1:4" -p "QCD-JESup:QCD-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:QCD_CMS_scale_j_8TeVUp:-1:2:2" -p "QCD-JESdown:QCD-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:QCD_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="QCD_jes_2jet2tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "W-central:W-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:W:-1:1:4" -p "W-JESup:W-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:W_CMS_scale_j_8TeVUp:-1:2:2" -p "W-JESdown:W-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:W_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="W_jes_2jet2tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZTT-central:ZTT-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ZTT:-1:1:4" -p "ZTT-JESup:ZTT-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ZTT_CMS_scale_j_8TeVUp:-1:2:2" -p "ZTT-JESdown:ZTT-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ZTT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZTT_jes_2jet2tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZJ-central:ZJ-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ZJ:-1:1:4" -p "ZJ-JESup:ZJ-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ZJ_CMS_scale_j_8TeVUp:-1:2:2" -p "ZJ-JESdown:ZJ-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ZJ_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZJ_jes_2jet2tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZL-central:ZL-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ZL:-1:1:4" -p "ZL-JESup:ZL-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ZL_CMS_scale_j_8TeVUp:-1:2:2" -p "ZL-JESdown:ZL-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:ZL_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZL_jes_2jet2tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "VV-central:VV-central:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:VV:-1:1:4" -p "VV-JESup:VV-JESup:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:VV_CMS_scale_j_8TeVUp:-1:2:2" -p "VV-JESdown:VV-JESdown:htt_mt.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:muTau_2jet2tag:VV_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="VV_jes_2jet2tag_mt" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ggHTohh300-central:ggHTohh300-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ggHTohhTo2Tau2B300:-1:1:4" -p "ggHTohh300-JESup:ggHTohh300-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVUp:-1:2:2" -p "ggHTohh300-JESdown:ggHTohh300-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ggHTohh300_jes_2jet0tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "TT-central:TT-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:TT:-1:1:4" -p "TT-JESup:TT-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:TT_CMS_scale_j_8TeVUp:-1:2:2" -p "TT-JESdown:TT-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:TT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="TT_jes_2jet0tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "QCD-central:QCD-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:QCD:-1:1:4" -p "QCD-JESup:QCD-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:QCD_CMS_scale_j_8TeVUp:-1:2:2" -p "QCD-JESdown:QCD-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:QCD_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="QCD_jes_2jet0tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "W-central:W-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:W:-1:1:4" -p "W-JESup:W-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:W_CMS_scale_j_8TeVUp:-1:2:2" -p "W-JESdown:W-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:W_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="W_jes_2jet0tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZTT-central:ZTT-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ZTT:-1:1:4" -p "ZTT-JESup:ZTT-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ZTT_CMS_scale_j_8TeVUp:-1:2:2" -p "ZTT-JESdown:ZTT-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ZTT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZTT_jes_2jet0tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZJ-central:ZJ-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ZJ:-1:1:4" -p "ZJ-JESup:ZJ-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ZJ_CMS_scale_j_8TeVUp:-1:2:2" -p "ZJ-JESdown:ZJ-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ZJ_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZJ_jes_2jet0tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZL-central:ZL-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ZL:-1:1:4" -p "ZL-JESup:ZL-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ZL_CMS_scale_j_8TeVUp:-1:2:2" -p "ZL-JESdown:ZL-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:ZL_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZL_jes_2jet0tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "VV-central:VV-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:VV:-1:1:4" -p "VV-JESup:VV-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:VV_CMS_scale_j_8TeVUp:-1:2:2" -p "VV-JESdown:VV-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet0tag:VV_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="VV_jes_2jet0tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ggHTohh300-central:ggHTohh300-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ggHTohhTo2Tau2B300:-1:1:4" -p "ggHTohh300-JESup:ggHTohh300-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVUp:-1:2:2" -p "ggHTohh300-JESdown:ggHTohh300-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ggHTohh300_jes_2jet1tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "TT-central:TT-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:TT:-1:1:4" -p "TT-JESup:TT-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:TT_CMS_scale_j_8TeVUp:-1:2:2" -p "TT-JESdown:TT-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:TT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="TT_jes_2jet1tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "QCD-central:QCD-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:QCD:-1:1:4" -p "QCD-JESup:QCD-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:QCD_CMS_scale_j_8TeVUp:-1:2:2" -p "QCD-JESdown:QCD-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:QCD_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="QCD_jes_2jet1tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "W-central:W-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:W:-1:1:4" -p "W-JESup:W-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:W_CMS_scale_j_8TeVUp:-1:2:2" -p "W-JESdown:W-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:W_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="W_jes_2jet1tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZTT-central:ZTT-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ZTT:-1:1:4" -p "ZTT-JESup:ZTT-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ZTT_CMS_scale_j_8TeVUp:-1:2:2" -p "ZTT-JESdown:ZTT-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ZTT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZTT_jes_2jet1tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZJ-central:ZJ-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ZJ:-1:1:4" -p "ZJ-JESup:ZJ-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ZJ_CMS_scale_j_8TeVUp:-1:2:2" -p "ZJ-JESdown:ZJ-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ZJ_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZJ_jes_2jet1tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZL-central:ZL-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ZL:-1:1:4" -p "ZL-JESup:ZL-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ZL_CMS_scale_j_8TeVUp:-1:2:2" -p "ZL-JESdown:ZL-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:ZL_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZL_jes_2jet1tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "VV-central:VV-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:VV:-1:1:4" -p "VV-JESup:VV-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:VV_CMS_scale_j_8TeVUp:-1:2:2" -p "VV-JESdown:VV-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet1tag:VV_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="VV_jes_2jet1tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ggHTohh300-central:ggHTohh300-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ggHTohhTo2Tau2B300:-1:1:4" -p "ggHTohh300-JESup:ggHTohh300-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVUp:-1:2:2" -p "ggHTohh300-JESdown:ggHTohh300-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ggHTohhTo2Tau2B300_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ggHTohh300_jes_2jet2tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "TT-central:TT-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:TT:-1:1:4" -p "TT-JESup:TT-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:TT_CMS_scale_j_8TeVUp:-1:2:2" -p "TT-JESdown:TT-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:TT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="TT_jes_2jet2tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "QCD-central:QCD-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:QCD:-1:1:4" -p "QCD-JESup:QCD-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:QCD_CMS_scale_j_8TeVUp:-1:2:2" -p "QCD-JESdown:QCD-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:QCD_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="QCD_jes_2jet2tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "W-central:W-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:W:-1:1:4" -p "W-JESup:W-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:W_CMS_scale_j_8TeVUp:-1:2:2" -p "W-JESdown:W-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:W_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="W_jes_2jet2tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZTT-central:ZTT-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ZTT:-1:1:4" -p "ZTT-JESup:ZTT-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ZTT_CMS_scale_j_8TeVUp:-1:2:2" -p "ZTT-JESdown:ZTT-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ZTT_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZTT_jes_2jet2tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZJ-central:ZJ-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ZJ:-1:1:4" -p "ZJ-JESup:ZJ-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ZJ_CMS_scale_j_8TeVUp:-1:2:2" -p "ZJ-JESdown:ZJ-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ZJ_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZJ_jes_2jet2tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "ZL-central:ZL-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ZL:-1:1:4" -p "ZL-JESup:ZL-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ZL_CMS_scale_j_8TeVUp:-1:2:2" -p "ZL-JESdown:ZL-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:ZL_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="ZL_jes_2jet2tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0

./bin/PlotCompare -p "VV-central:VV-central:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:VV:-1:1:4" -p "VV-JESup:VV-JESup:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:VV_CMS_scale_j_8TeVUp:-1:2:2" -p "VV-JESdown:VV-JESdown:htt_et.inputs-Hhh-8TeV-mH_masscuts_reducedBinning.root:eleTau_2jet2tag:VV_CMS_scale_j_8TeVDown:-1:2:4" --norm_mode=3 --big_label="#mu#tau_{h}"  --outname="VV_jes_2jet2tag_et" --x_axis_title="m_{H}^{kinfit}  [GeV]"  --norm_bins=true  --custom_y_axis_min=true --y_axis_min=0.0
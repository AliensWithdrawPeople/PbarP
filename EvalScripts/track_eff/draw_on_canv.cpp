#include <vector>
#include <map>
#include <iostream>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TH1D.h>

int draw_on_canv()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //
    // Season: HIGH2022
    std::vector<std::string> names_season_HIGH2022 = {"season_HIGH2022_elabel950_119028_track_eff_res.root", "season_HIGH2022_elabel951_119974_track_eff_res.root", "season_HIGH2022_elabel952_118137_track_eff_res.root", "season_HIGH2022_elabel953_118524_track_eff_res.root", "season_HIGH2022_elabel954_119518_track_eff_res.root"};
    std::vector<std::string> label_season_HIGH2022 = {"119028", "119974", "118137", "118524", "119518"};
    // Season: HIGH2019
    std::vector<std::string> names_season_HIGH2019 = {"season_HIGH2019_elabel950_79625_track_eff_res.root", "season_HIGH2019_elabel955_81775_track_eff_res.root", "season_HIGH2019_elabel962.5_80068_track_eff_res.root", "season_HIGH2019_elabel975_80603_track_eff_res.root", "season_HIGH2019_elabel978_80506_track_eff_res.root", "season_HIGH2019_elabel987.5_81313_track_eff_res.root"};
    std::vector<std::string> label_season_HIGH2019 = {"79625", "81775", "80068", "80603", "80506", "81313"};
    // Season: HIGH2020
    std::vector<std::string> names_season_HIGH2020 = {"season_HIGH2020_elabel950_93145_track_eff_res.root", "season_HIGH2020_elabel960_94254_track_eff_res.root", "season_HIGH2020_elabel970_95392_track_eff_res.root"};
    std::vector<std::string> label_season_HIGH2020 = {"93145", "94254", "95392"};
    // Season: HIGH2021
    std::vector<std::string> names_season_HIGH2021 = {"season_HIGH2021_elabel970_98116_track_eff_res.root", "season_HIGH2021_elabel980_99550_track_eff_res.root", "season_HIGH2021_elabel990_101920_track_eff_res.root", "season_HIGH2021_elabel1003.5_103608_track_eff_res.root"};
    std::vector<std::string> label_season_HIGH2021 = {"98116", "99550", "101920", "103608"};

    std::map<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>> seasons = { {"season_HIGH2022", {names_season_HIGH2022, label_season_HIGH2022}}, 
                                                                {"season_HIGH2019", {names_season_HIGH2019, label_season_HIGH2019}}, 
                                                                {"season_HIGH2020", {names_season_HIGH2020, label_season_HIGH2020}}, 
                                                                {"season_HIGH2021", {names_season_HIGH2021, label_season_HIGH2021}}};

    // ********************* End of Data ********************* //

    TFile res("effs.root", "recreate");
    // std::string 
    for(const auto& [season, names] : seasons)
    {
        auto canv = new TCanvas(("ratio_" + season).c_str());
        canv->Divide((names.first.size() > 4)? 3 : 2, 2);
        for(int i = 1; i < names.first.size() + 1; i++)
        {
            std::cout << names.first[i-1] << " : " << ("ratio_" + names.second[i-1]) << std::endl;
            auto eff = TFile(("C:/work/Science/BINP/PbarP/EvalScripts/track_eff/results/" + names.first[i-1]).c_str()).Get<TCanvas>(("eff_" + names.second[i-1]).c_str());
            auto ratio = TFile(("C:/work/Science/BINP/PbarP/EvalScripts/track_eff/results/" + names.first[i-1]).c_str()).Get<TCanvas>(("ratio_" + names.second[i-1]).c_str());
            res.cd();
            canv->cd(i);
            // eff->DrawClonePad();
            ratio->DrawClonePad();
        }
        res.cd();
        canv->Draw();
        canv->Write();
    }
    res.Save();

    return 0;
}
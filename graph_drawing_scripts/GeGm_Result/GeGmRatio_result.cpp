#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH2D.h>

int GeGmRatio_result()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    std::vector<double> nominal_energy_season2017 = {936, 945, 950, 955, 962.5, 975, 978, 987.5};
    std::vector<double> nominal_energy_season2019 = {936, 945, 950, 955, 962.5, 975, 978, 987.5};
    std::vector<double> nominal_energy_season2020 = {935, 945, 950, 960, 970};
    std::vector<double> nominal_energy_season2021 = {970, 980, 990, 1003.5};
    std::vector<double> nominal_energy_season2022 = {920, 930, 935, 937.5, 938.3, 938.9, 939.6, 940.2, 941, 942, 943.5, 945, 947.5, 948.75, 950, 951, 952, 953, 954};

    // ********************* Start of Data ********************* //

    //HIGH2021
    std::vector<double> energy_HIGH2021 = { 1003.5, 968.805, 980.248, 990.293 }; // MeV
    std::vector<double> gegm_HIGH2021 = { 1.1152, 1.0039, 1.2394, 1.0588 };
    std::vector<double> gegm_err_HIGH2021 = { 0.0426, 0.0872, 0.0698, 0.0596 };
    std::vector<double> chi2_HIGH2021 = { 1.4154, 1.3701, 0.992, 1.0335 };

    //HIGH2022
    std::vector<double> energy_HIGH2022 = { 949.995, 952.012, 953.003, 953.997 }; // MeV
    std::vector<double> gegm_HIGH2022 = { 2.0396, 0, 0.1768, 0 };
    std::vector<double> gegm_err_HIGH2022 = { 0.5792, 0, 0.0, 0 };
    std::vector<double> chi2_HIGH2022 = { 21.2422, 24.4644, 3.5323, 6.6363 };

    //HIGH2019
    std::vector<double> energy_HIGH2019 = { 950.15, 956.084, 962.687, 972.917, 977.158, 987.81 }; // MeV
    std::vector<double> gegm_HIGH2019 = { 0, 2.3428, 0, 0.9848, 0.1165, 1.193 };
    std::vector<double> gegm_err_HIGH2019 = { 0, 1.0644, 0, 0.1034, 0.0, 0.1458 };
    std::vector<double> chi2_HIGH2019 = { 119.5332, 0.8921, 0.7584, 0.8911, 1.4042, 0.6519 };

    //HIGH2020
    std::vector<double> energy_HIGH2020 = { 950.29, 960.252, 970.583 }; // MeV
    std::vector<double> gegm_HIGH2020 = { 1.3401, 1.1989, 1.1938 };
    std::vector<double> gegm_err_HIGH2020 = { 0.3815, 0.0887, 0.0816 };
    std::vector<double> chi2_HIGH2020 = { 318.3026, 1.1753, 0.5875 };

    // ********************* End of Data ********************* //
        
    // season2019
    TGraphErrors gegm_vs_energy_season2019(energy_HIGH2019.size(), energy_HIGH2019.data(), gegm_HIGH2019.data(), 
                                            zeroes.data(), gegm_err_HIGH2019.data());
    TGraphErrors chi2_vs_energy_season2019(energy_HIGH2019.size(), energy_HIGH2019.data(), chi2_HIGH2019.data(), 
                                            zeroes.data(), zeroes.data());

    gegm_vs_energy_season2019.SetMarkerColor(kRed);
    gegm_vs_energy_season2019.SetName("gegm_vs_energy_season2019");

    chi2_vs_energy_season2019.SetMarkerColor(kRed);
    chi2_vs_energy_season2019.SetName("chi2_vs_energy_season2019");

    // season2020
    TGraphErrors gegm_vs_energy_season2020(energy_HIGH2020.size(), energy_HIGH2020.data(), gegm_HIGH2020.data(), 
                                            zeroes.data(), gegm_err_HIGH2020.data());
    TGraphErrors chi2_vs_energy_season2020(energy_HIGH2020.size(), energy_HIGH2020.data(), chi2_HIGH2020.data(), 
                                            zeroes.data(), zeroes.data());

    gegm_vs_energy_season2020.SetMarkerColor(kBlue);
    gegm_vs_energy_season2020.SetName("gegm_vs_energy_season2020");

    chi2_vs_energy_season2020.SetMarkerColor(kBlue);
    chi2_vs_energy_season2020.SetName("chi2_vs_energy_season2020");

    // season2021
    TGraphErrors gegm_vs_energy_season2021(energy_HIGH2021.size(), energy_HIGH2021.data(), gegm_HIGH2021.data(), 
                                            zeroes.data(), gegm_err_HIGH2021.data());
    TGraphErrors chi2_vs_energy_season2021(energy_HIGH2021.size(), energy_HIGH2021.data(), chi2_HIGH2021.data(), 
                                            zeroes.data(), zeroes.data());

    gegm_vs_energy_season2021.SetMarkerColor(kMagenta);
    gegm_vs_energy_season2021.SetName("gegm_vs_energy_season2021");

    chi2_vs_energy_season2021.SetMarkerColor(kMagenta);
    chi2_vs_energy_season2021.SetName("chi2_vs_energy_season2021");

    // season2022
    TGraphErrors gegm_vs_energy_season2022(energy_HIGH2022.size(), energy_HIGH2022.data(), gegm_HIGH2022.data(), 
                                            zeroes.data(), gegm_err_HIGH2022.data());
    TGraphErrors chi2_vs_energy_season2022(energy_HIGH2022.size(), energy_HIGH2022.data(), chi2_HIGH2022.data(), 
                                            zeroes.data(), zeroes.data());

    gegm_vs_energy_season2022.SetMarkerColor(kBlack);
    gegm_vs_energy_season2022.SetName("gegm_vs_energy_season2022");

    chi2_vs_energy_season2022.SetMarkerColor(kBlack);
    chi2_vs_energy_season2022.SetName("chi2_vs_energy_season2022");
    
    auto hist = new TH2D("hist", "", 3, 940, 1010, 3, 0, 2.4);
    hist->GetXaxis()->SetTitle("E_{beam}, MeV");
    hist->GetYaxis()->SetTitle("|G_{e}/G_{m}|");
    hist->Draw();

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Seasons","C"); // option "C" allows to center the header



    gegm_vs_energy_season2019.DrawClone("P");
    gegm_vs_energy_season2020.DrawClone("P");
    gegm_vs_energy_season2021.DrawClone("P");
    gegm_vs_energy_season2022.DrawClone("P");
    legend->AddEntry("gegm_vs_energy_season2019","High2019","ep");
    legend->AddEntry("gegm_vs_energy_season2020","High2020","ep");
    legend->AddEntry("gegm_vs_energy_season2021","High2021","ep");
    legend->AddEntry("gegm_vs_energy_season2022","NNbar2022","ep");


    legend->DrawClone();
    canv.DrawClone();
    return 0;
}
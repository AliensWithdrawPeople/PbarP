#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH2D.h>

int GeGmRatio_result_no_eff_correction()
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
    std::vector<double> gegm_HIGH2021 = { 1.1928, 1.4896, 1.3987, 1.2535 };
    std::vector<double> gegm_err_HIGH2021 = { 0.0468, 0.1386, 0.0822, 0.072 };
    std::vector<double> chi2_HIGH2021 = { 1.4867, 1.1268, 1.048, 0.945 };

    //HIGH2022
    std::vector<double> energy_HIGH2022 = { 949.995, 950.945, 952.012, 953.003, 953.997 }; // MeV
    std::vector<double> gegm_HIGH2022 = { 1.2487, 1.8262, 0, 0.4188, 0 };
    std::vector<double> gegm_err_HIGH2022 = { 0.376, 0.8256, 0, 0.2143, 0 };
    std::vector<double> chi2_HIGH2022 = { 0.7916, 1.6299, 3.5875, 5.5442, 1.4148 };

    //HIGH2019
    std::vector<double> energy_HIGH2019 = { 950.15, 956.084, 962.687, 972.917, 977.158, 987.81 }; // MeV
    std::vector<double> gegm_HIGH2019 = { 0, 0, 0, 0.8453, 0.4853, 1.1546 };
    std::vector<double> gegm_err_HIGH2019 = { 0, 0, 0, 0.0953, 0.2959, 0.1439 };
    std::vector<double> chi2_HIGH2019 = { 0.2066, 1.1466, 1.1257, 1.6196, 1.1371, 1.2638 };

    //HIGH2020
    std::vector<double> energy_HIGH2020 = { 950.29, 960.252, 970.583 }; // MeV
    std::vector<double> gegm_HIGH2020 = { 1.6192, 1.252, 1.2318 };
    std::vector<double> gegm_err_HIGH2020 = { 0.4492, 0.0945, 0.0852 };
    std::vector<double> chi2_HIGH2020 = { 1.39, 1.4351, 0.6843 };

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



    hist->SetTitle("Quality of fit for |G_{e}/G_{m}|");
    hist->GetYaxis()->SetTitle("#chi^{2}/ndf");
    chi2_vs_energy_season2019.DrawClone("P");
    chi2_vs_energy_season2020.DrawClone("P");
    chi2_vs_energy_season2021.DrawClone("P");
    chi2_vs_energy_season2022.DrawClone("P");

    legend->AddEntry("chi2_vs_energy_season2019","High2019","ep");
    legend->AddEntry("chi2_vs_energy_season2020","High2020","ep");
    legend->AddEntry("chi2_vs_energy_season2021","High2021","ep");
    legend->AddEntry("chi2_vs_energy_season2022","NNbar2022","ep");


    legend->DrawClone();
    canv.DrawClone();
    return 0;
}
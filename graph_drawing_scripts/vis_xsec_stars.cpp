#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int vis_xsec_stars()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);

    // ********************* Start of Data ********************* //

    //// season2017
    std::vector<double> nominal_energy_season2017 ={930, 936, 937.4, 937.5, 938.3, 938.9, 939.6, 940.2, 940.8, 942, 950, 960, 971, 981}; // MeV
    std::vector<double> energy_season2017 ={930.481, 935.478, 937.388, 937.218, 938.176, 938.723, 939.467, 940.166, 940.608, 941.882, 950.359, 960.625, 971.253, 981.947}; // MeV
    std::vector<double> xsec_season2017 = {-0.0003, 0.0014, 0.0089, 0.0031, 0.0119, 0.025, 0.0404, 0.0452, 0.0525, 0.0534, 0.0436, 0.0079, 0.0044, 0.0066}; // nb
    std::vector<double> xsec_err_season2017 = {0.0027, 0.0033, 0.0037, 0.0044, 0.004, 0.0051, 0.0062, 0.0063, 0.007, 0.0085, 0.0078, 0.005, 0.0034, 0.0038}; // nb


    //// season2019
    std::vector<double> nominal_energy_season2019 ={936, 945, 950, 955, 962.5, 975, 978, 987.5}; // MeV
    std::vector<double> energy_season2019 ={936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> xsec_season2019 = {0.0013, 0.0756, 0.0453, 0.0109, 0.012, 0.0039, 0.0048, 0.0014}; // nb
    std::vector<double> xsec_err_season2019 = {0.0027, 0.0075, 0.0071, 0.0051, 0.0041, 0.0023, 0.0062, 0.0027}; // nb


    //// season2020
    std::vector<double> nominal_energy_season2020 ={935, 945, 950, 960, 970}; // MeV
    std::vector<double> energy_season2020 ={934.705, 945.461, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> xsec_season2020 = {0.0027, 0.071, 0.0408, 0.0076, 0.0066}; // nb
    std::vector<double> xsec_err_season2020 = {0.0013, 0.0037, 0.0029, 0.0016, 0.0016}; // nb


    //// season2021
    std::vector<double> nominal_energy_season2021 ={1003.5, 970, 980, 990}; // MeV
    std::vector<double> energy_season2021 ={1003.5, 968.805, 980.248, 990.293}; // MeV
    std::vector<double> xsec_season2021 = {0.0038, 0.0094, 0.0082, 0.0046}; // nb
    std::vector<double> xsec_err_season2021 = {0.0009, 0.0023, 0.0016, 0.0014}; // nb


    //// season2022
    std::vector<double> nominal_energy_season2022 ={920, 930, 935, 937.5, 938.3, 938.9, 939.6, 940.2, 941, 942, 943.5, 945, 947.5, 948.75, 950, 951, 952, 953, 954}; // MeV
    std::vector<double> energy_season2022 ={919.966, 929.985, 934.979, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 948.727, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> xsec_season2022 = {0.0006, 0.0032, 0.002, 0.0028, 0.0158, 0.0325, 0.0435, 0.048, 0.05, 0.057, 0.0592, 0.0592, 0.0671, 0.0628, 0.0386, 0.0251, 0.0256, 0.0185, 0.012}; // nb
    std::vector<double> xsec_err_season2022 = {0.0011, 0.0013, 0.001, 0.0012, 0.0017, 0.0025, 0.0028, 0.0029, 0.003, 0.0032, 0.0032, 0.003, 0.0031, 0.004, 0.0038, 0.0032, 0.0033, 0.0028, 0.0028}; // nb


    // ********************* End of Data ********************* //
    // season2017
    TGraphErrors xsec_vs_energy_season2017(energy_season2017.size(), energy_season2017.data(), xsec_season2017.data(), 
                                            zeroes.data(), xsec_err_season2017.data());
    xsec_vs_energy_season2017.SetMarkerColor(kGreen);
    xsec_vs_energy_season2017.SetName("xsec_vs_energy_season2017");
    xsec_vs_energy_season2017.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_season2017.GetYaxis()->SetTitle("#sigma^{(vis)}_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_season2017.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} annihilation events");


    // season2019
    TGraphErrors xsec_vs_energy_season2019(energy_season2019.size(), energy_season2019.data(), xsec_season2019.data(), 
                                            zeroes.data(), xsec_err_season2019.data());
    xsec_vs_energy_season2019.SetMarkerColor(kRed);

    // season2020
    TGraphErrors xsec_vs_energy_season2020(energy_season2020.size(), energy_season2020.data(), xsec_season2020.data(), 
                                            zeroes.data(), xsec_err_season2020.data());
    xsec_vs_energy_season2020.SetMarkerColor(kBlue);
    xsec_vs_energy_season2020.SetName("xsec_vs_energy_season2020");

    // season2021
    TGraphErrors xsec_vs_energy_season2021(energy_season2021.size(), energy_season2021.data(), xsec_season2021.data(), 
                                            zeroes.data(), xsec_err_season2021.data());
    xsec_vs_energy_season2021.SetMarkerColor(kMagenta);
    xsec_vs_energy_season2021.SetName("xsec_vs_energy_season2021");

    // season2022
    TGraphErrors xsec_vs_energy_season2022(energy_season2022.size(), energy_season2022.data(), xsec_season2022.data(), 
                                            zeroes.data(), xsec_err_season2022.data());
    xsec_vs_energy_season2022.SetMarkerColor(kBlack);
    xsec_vs_energy_season2022.SetName("xsec_vs_energy_season2022");

    xsec_vs_energy_season2017.DrawClone("AP");
    xsec_vs_energy_season2019.DrawClone("P same");
    xsec_vs_energy_season2020.DrawClone("P same");
    xsec_vs_energy_season2021.DrawClone("P same");
    xsec_vs_energy_season2022.DrawClone("P same");

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Seasons","C"); // option "C" allows to center the header
    legend->AddEntry("xsec_vs_energy_season2017","High2017","ep");
    legend->AddEntry("xsec_vs_energy_season2019","High2019","ep");
    legend->AddEntry("xsec_vs_energy_season2020","High2020","ep");
    legend->AddEntry("xsec_vs_energy_season2021","High2021","ep");
    legend->AddEntry("xsec_vs_energy_season2022","NNbar2022","ep");
    legend->DrawClone();

    canv.DrawClone();
    return 0;
}
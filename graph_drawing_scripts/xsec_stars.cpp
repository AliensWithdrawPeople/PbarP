#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int xsec_stars()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //

    //season2017
    std::vector<double> energy_season2017 = {930.481, 935.478, 938.176, 938.723, 939.467, 940.166, 940.608, 941.882, 950.359, 960.625, 971.253, 981.947}; // MeV
    std::vector<double> xsec_season2017 = {0.0002, 0.003, 0.0122, 0.3494, 0.4567, 0.5616, 0.675, 0.709, 0.8921, 1.9181, 1.3452, 2.7515}; // nb
    std::vector<double> xsec_err_season2017 = {0.0019, 0.0033, 0.0034, 0.0941, 0.1158, 0.1369, 0.1551, 0.1717, 0.3029, 3.1916, 5.0457, 15.3312}; // nb

    //season2019
    std::vector<double> energy_season2019 = {936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> xsec_season2019 = {-0.0005, 0.7852, 1.2028, 1.4613, 1.7759, 2.4599, -0.4069, 3.5311}; // nb
    std::vector<double> xsec_err_season2019 = {0.0018, 0.1698, 0.2994, 1.6344, 4.1759, 8.5585, 2.7829, 19.1151}; // nb

    //season2020
    std::vector<double> energy_season2020 = {934.705, 945.461, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> xsec_season2020 = {0.0009, 0.8201, 0.9628, 1.2511, 1.8356}; // nb
    std::vector<double> xsec_err_season2020 = {0.0009, 0.1621, 0.5948, 1.991, 6.4141}; // nb

    //season2021
    std::vector<double> energy_season2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> xsec_season2021 = {3.6916, 5.3227, 2.5038, 4.5153}; // nb
    std::vector<double> xsec_err_season2021 = {11.8356, 27.5728, 15.1656, 35.6921}; // nb

    //season2022
    std::vector<double> energy_season2022 = {919.966, 929.985, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> xsec_season2022 = {-0.0001, 0.0022, 0.0018, 0.5277, 0.3874, 0.5496, 0.5941, 0.6222, 0.6919, 0.7141, 0.7584, 0.8164, 0.7973, 0.8652, 0.7395, 0.7784, 0.768}; // nb
    std::vector<double> xsec_err_season2022 = {0.0007, 0.001, 0.0009, 0.1638, 0.0807, 0.1111, 0.1189, 0.1252, 0.1382, 0.142, 0.1512, 0.1639, 0.5915, 0.8157, 0.2123, 0.4912, 0.421}; // nb

    // ********************* End of Data ********************* //

    // season2017
    TGraphErrors xsec_vs_energy_season2017(energy_season2017.size(), energy_season2017.data(), xsec_season2017.data(), 
                                            zeroes.data(), xsec_err_season2017.data());
    xsec_vs_energy_season2017.SetMarkerColor(kGreen);
    xsec_vs_energy_season2017.SetName("xsec_vs_energy_season2017");
    xsec_vs_energy_season2017.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_season2017.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_season2017.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} annihilation events");

    // season2019
    TGraphErrors xsec_vs_energy_season2019(energy_season2019.size(), energy_season2019.data(), xsec_season2019.data(), 
                                            zeroes.data(), xsec_err_season2019.data());
    xsec_vs_energy_season2019.SetMarkerColor(kRed);
    xsec_vs_energy_season2019.SetName("xsec_vs_energy_season2019");

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
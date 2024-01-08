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
    std::vector<double> energy_season2017 = {938.723, 939.467, 940.166, 940.608, 941.882, 950.359, 960.625, 971.253, 981.947}; // MeV
    std::vector<double> xsec_season2017 = {0.1443, 0.1886, 0.2319, 0.2788, 0.2928, 0.3684, 0.7922, 0.5556, 1.1364}; // nb
    std::vector<double> xsec_err_season2017 = {0.0285, 0.0337, 0.0377, 0.0401, 0.0475, 0.0857, 0.3954, 0.5356, 0.9773}; // nb

    //season2019
    std::vector<double> energy_season2019 = {944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> xsec_season2019 = {0.3243, 0.4128, 0.4262, 0.7594, 1.0682, -0.174, 1.4485}; // nb
    std::vector<double> xsec_err_season2019 = {0.0407, 0.0607, 0.2423, 0.4397, 0.5164, 0.9531, 0.9331}; // nb

    //season2020
    std::vector<double> energy_season2020 = {945.461, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> xsec_season2020 = {0.3387, 0.3643, 0.4885, 0.762}; // nb
    std::vector<double> xsec_err_season2020 = {0.0296, 0.086, 0.1356, 0.2956}; // nb

    //season2021
    std::vector<double> energy_season2021 = {1003.5, 968.805, 980.248, 990.293}; // MeV
    std::vector<double> xsec_season2021 = {1.8648, 1.4955, 2.1015, 1.049}; // nb
    std::vector<double> xsec_err_season2021 = {0.4135, 0.4677, 0.4914, 0.4229}; // nb

    //season2022
    std::vector<double> energy_season2022 = {938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> xsec_season2022 = {0.2179, 0.16, 0.227, 0.2454, 0.257, 0.2858, 0.2949, 0.3132, 0.3372, 0.3186, 0.309, 0.4054, 0.4011, 0.4251}; // nb
    std::vector<double> xsec_err_season2022 = {0.0262, 0.0165, 0.0211, 0.0222, 0.0233, 0.0254, 0.0259, 0.0267, 0.029, 0.0963, 0.1445, 0.0575, 0.1063, 0.2163}; // nb

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
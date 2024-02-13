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
    std::vector<double> xsec_season2017 = {-0.0003, 0.0014, 0.0119, 0.3305, 0.5027, 0.5799, 0.638, 0.6579, 1.1416, 1.8219, 2.213, 5.062}; // nb
    std::vector<double> xsec_err_season2017 = {0.0027, 0.0033, 0.004, 0.0896, 0.1172, 0.1306, 0.1402, 0.1557, 0.3403, 3.1714, 7.9839, 27.3432}; // nb

    //season2019
    std::vector<double> energy_season2019 = {936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> xsec_season2019 = {0.0013, 0.8531, 1.2272, 1.6884, 2.9021, 1.9619, 2.8133, 1.056}; // nb
    std::vector<double> xsec_err_season2019 = {0.0027, 0.1692, 0.3041, 1.9951, 6.4916, 7.02, 12.2954, 5.9428}; // nb

    //season2020
    std::vector<double> energy_season2020 = {934.705, 945.461, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> xsec_season2020 = {0.0027, 0.8238, 1.0095, 1.718, 3.2175}; // nb
    std::vector<double> xsec_err_season2020 = {0.0013, 0.1486, 0.5591, 2.7568, 11.0172}; // nb

    //season2021
    std::vector<double> energy_season2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> xsec_season2021 = {4.3079, 5.9388, 3.8302, 4.1784}; // nb
    std::vector<double> xsec_err_season2021 = {13.8809, 30.1391, 22.3593, 32.1783}; // nb

    //season2022
    std::vector<double> energy_season2022 = {919.966, 929.985, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> xsec_season2022 = {0.0006, 0.0032, 0.0028, 0.523, 0.4126, 0.5347, 0.5738, 0.6111, 0.6856, 0.7054, 0.7362, 0.8532, 0.8515, 0.8885, 0.8399, 0.882, 0.706}; // nb
    std::vector<double> xsec_err_season2022 = {0.0011, 0.0013, 0.0012, 0.1556, 0.0794, 0.0997, 0.1056, 0.1129, 0.1254, 0.1284, 0.1345, 0.1557, 0.5655, 0.7527, 0.2298, 0.5114, 0.379}; // nb

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
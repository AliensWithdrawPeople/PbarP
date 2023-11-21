#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int xsec_coll()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //

    //season2019
    std::vector<double> energy_season2019 = {950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> xsec_season2019 = {5.9777, 1.0132, 1.0961, 0.7713, 0.8516, 0.7373}; // nb
    std::vector<double> xsec_err_season2019 = {2.6313, 0.298, 0.4891, 0.1606, 0.6738, 0.184}; // nb

    //season2020
    std::vector<double> energy_season2020 = {950.29, 960.252, 970.583}; // MeV
    std::vector<double> xsec_season2020 = {2.7865, 0.903, 0.7464}; // nb
    std::vector<double> xsec_err_season2020 = {0.7135, 0.1412, 0.1146}; // nb

    //season2021
    std::vector<double> energy_season2021 = {1003.5, 968.805, 980.248, 990.293}; // MeV
    std::vector<double> xsec_season2021 = {0.7647, 0.7453, 0.7348, 0.6811}; // nb
    std::vector<double> xsec_err_season2021 = {0.074, 0.1384, 0.0946, 0.0847}; // nb

    //season2022
    std::vector<double> energy_season2022 = {949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> xsec_season2022 = {48.2519, 1.4444, 3.4112, 2.3911, 1.5605}; // nb
    std::vector<double> xsec_err_season2022 = {17.0813, 0.5669, 0.319, 0.7602, 1.056}; // nb

    // ********************* End of Data ********************* //

    // season2019
    TGraphErrors xsec_vs_energy_season2019(energy_season2019.size(), energy_season2019.data(), xsec_season2019.data(), 
                                            zeroes.data(), xsec_err_season2019.data());
    xsec_vs_energy_season2019.SetMarkerColor(kRed);
    xsec_vs_energy_season2019.SetName("xsec_vs_energy_season2019");
    xsec_vs_energy_season2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_season2019.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_season2019.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} collinear events");

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

    xsec_vs_energy_season2019.DrawClone("AP");
    xsec_vs_energy_season2020.DrawClone("P same");
    xsec_vs_energy_season2021.DrawClone("P same");
    xsec_vs_energy_season2022.DrawClone("P same");

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Seasons","C"); // option "C" allows to center the header
    legend->AddEntry("xsec_vs_energy_season2019","High2019","ep");
    legend->AddEntry("xsec_vs_energy_season2020","High2020","ep");
    legend->AddEntry("xsec_vs_energy_season2021","High2021","ep");
    legend->AddEntry("xsec_vs_energy_season2022","NNbar2022","ep");
    legend->DrawClone();

    canv.DrawClone();
    return 0;
}
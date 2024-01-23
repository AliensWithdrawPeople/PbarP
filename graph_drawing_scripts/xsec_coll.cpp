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
    std::vector<double> xsec_season2019 = {5.9777, 0.9989, 1.1865, 0.8842, 0.9152, 0.7781}; // nb
    std::vector<double> xsec_err_season2019 = {2.6308, 0.0561, 1.0839, 0.102, 0.3919, 0.0955}; // nb

    //season2020
    std::vector<double> energy_season2020 = {950.29, 960.252, 970.583}; // MeV
    std::vector<double> xsec_season2020 = {2.9087, 0.8564, 0.7517}; // nb
    std::vector<double> xsec_err_season2020 = {0.7561, 0.0605, 0.0495}; // nb

    //season2021
    std::vector<double> energy_season2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> xsec_season2021 = {0.7173, 0.7023, 0.7077, 0.7604}; // nb
    std::vector<double> xsec_err_season2021 = {0.0555, 0.0363, 0.0386, 0.0298}; // nb

    //season2022
    std::vector<double> energy_season2022 = {949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> xsec_season2022 = {48.2519, 1.4853, 3.4112, 2.1058, 1.5605}; // nb
    std::vector<double> xsec_err_season2022 = {17.0823, 0.4465, 0.3195, 0.7074, 0.3582}; // nb

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

    xsec_vs_energy_season2019.GetXaxis()->SetLimits(940, 1010);

    xsec_vs_energy_season2019.DrawClone("A  P");
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
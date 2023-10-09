#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH2D.h>

int xsec_bkg()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    std::vector<double> nominal_energy_season2017 = {936, 945, 950, 955, 962.5, 975, 978, 987.5};
    std::vector<double> nominal_energy_season2019 = {936, 945, 950, 955, 962.5, 975, 978, 987.5};
    std::vector<double> nominal_energy_season2020 = {935, 945, 950, 960, 970};
    std::vector<double> nominal_energy_season2021 = {970, 980, 990, 1003.5};
    std::vector<double> nominal_energy_season2022 = {920, 930, 935, 937.5, 938.3, 938.9, 939.6, 940.2, 941, 942, 943.5, 945, 947.5, 948.75, 950, 951, 952, 953, 954};

    // ********************* Start of Data ********************* //
    // season2017
    std::vector<double> energy_season2017 ={ 930.481, 935.478, 937.388, 937.218, 938.176, 938.723, 939.467, 940.166, 940.608, 941.882, 950.359, 960.625, 971.253, 981.947 }; // MeV
    std::vector<double> xsec_season2017 = { 0.0611, 0.0596, 0.0463, 0.0591, 0.0421, 0.0442, 0.0379, 0.0438, 0.0396, 0.0459, 0.0495, 0.0636, 0.0387, 0.0482 }; // nb
    std::vector<double> xsec_err_season2017 = { 0.008, 0.0095, 0.0063, 0.0092, 0.0053, 0.006, 0.0058, 0.0061, 0.006, 0.0076, 0.0088, 0.0087, 0.0062, 0.0079 }; // nb

    // season2019
    std::vector<double> energy_season2019 ={ 936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81 }; // MeV
    std::vector<double> xsec_season2019 = { 0.0501, 0.0449, 0.033, 0.043, 0.0366, 0.0423, 0.0266, 0.0473 }; // nb
    std::vector<double> xsec_err_season2019 = { 0.0064, 0.0055, 0.0056, 0.0075, 0.0057, 0.0042, 0.0108, 0.006 }; // nb

    // season2020
    std::vector<double> energy_season2020 ={ 934.705, 945.461, 950.29, 960.252, 970.583 }; // MeV
    std::vector<double> xsec_season2020 = { 0.0315, 0.0369, 0.0281, 0.0316, 0.0228 }; // nb
    std::vector<double> xsec_err_season2020 = { 0.0024, 0.0026, 0.0022, 0.0023, 0.0021 }; // nb

    // season2021
    std::vector<double> energy_season2021 ={ 1003.5, 968.805, 980.248, 990.293 }; // MeV
    std::vector<double> xsec_season2021 = { 0.0557, 0.0893, 0.0812, 0.0547 }; // nb
    std::vector<double> xsec_err_season2021 = { 0.002, 0.0052, 0.0034, 0.0029 }; // nb

    // season2022
    std::vector<double> energy_season2022 ={ 919.966, 929.985, 934.979, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 948.727, 949.995, 950.945, 952.012, 953.003, 953.997 }; // MeV
    std::vector<double> xsec_season2022 = { 0.0209, 0.025, 0.0179, 0.0382, 0.0282, 0.0316, 0.0332, 0.0301, 0.0335, 0.0322, 0.0352, 0.0336, 0.0279, 0.0254, 0.0305, 0.0387, 0.0288, 0.0259, 0.0258 }; // nb        
    std::vector<double> xsec_err_season2022 = { 0.0019, 0.0021, 0.0014, 0.0025, 0.0018, 0.0022, 0.0022, 0.0021, 0.0023, 0.0023, 0.0024, 0.0021, 0.0021, 0.0024, 0.0031, 0.0033, 0.003, 0.0028, 0.0029 }; // nb 
    // ********************* End of Data ********************* //
    
    // season2017
    TGraphErrors xsec_vs_energy_season2017(energy_season2017.size(), energy_season2017.data(), xsec_season2017.data(), 
                                            zeroes.data(), xsec_err_season2017.data());
    xsec_vs_energy_season2017.SetMarkerColor(kGreen);
    xsec_vs_energy_season2017.SetName("xsec_vs_energy_season2017");
    
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
    
    auto hist = new TH2D("hist", "hist", 3, 910, 1010, 3, -0.01, 0.08);
    hist->GetXaxis()->SetTitle("E_{beam}, MeV");
    hist->GetYaxis()->SetTitle("#sigma^{(vis)}_{e^{+}e^{-} #rightarrow p#bar{p}} bkg, nb");
    hist->SetTitle("e^{+}e^{-} #rightarrow p#bar{p} annihilation events");
    hist->Draw();

    xsec_vs_energy_season2017.DrawClone("P");
    xsec_vs_energy_season2019.DrawClone("P");
    xsec_vs_energy_season2020.DrawClone("P");
    xsec_vs_energy_season2021.DrawClone("P");
    xsec_vs_energy_season2022.DrawClone("P");

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
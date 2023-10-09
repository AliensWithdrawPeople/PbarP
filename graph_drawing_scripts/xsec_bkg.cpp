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
    // season2017
    std::vector<double> energy_season2017 ={ 930.481, 935.478, 937.388, 937.218, 938.176, 938.723, 939.467, 940.166, 940.608, 941.882, 950.359, 960.625, 971.253, 981.947 }; // MeV
    std::vector<double> xsec_season2017 = { 0.0066, 0.0143, 0.0116, 0.0115, 0.0115, 0.0107, 0.0097, 0.0161, 0.0115, 0.0119, 0.0114, 0.0172, 0.0066, 0.0106 }; // nb
    std::vector<double> xsec_err_season2017 = { 0.003, 0.005, 0.0032, 0.0044, 0.003, 0.0032, 0.0032, 0.0038, 0.0034, 0.0042, 0.0045, 0.0044, 0.003, 0.0042 }; // nb

    // season2019
    std::vector<double> energy_season2019 ={ 936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81 }; // MeV
    std::vector<double> xsec_season2019 = { 0.011, 0.0148, 0.0082, 0.0101, 0.0102, 0.0101, 0.007, 0.012 }; // nb
    std::vector<double> xsec_err_season2019 = { 0.0035, 0.0035, 0.0032, 0.004, 0.0034, 0.0022, 0.0059, 0.0033 }; // nb

    // season2020
    std::vector<double> energy_season2020 ={ 934.705, 945.461, 950.29, 960.252, 970.583 }; // MeV
    std::vector<double> xsec_season2020 = { 0.0063, 0.0113, 0.0073, 0.0086, 0.0044 }; // nb
    std::vector<double> xsec_err_season2020 = { 0.0012, 0.0015, 0.0012, 0.0013, 0.0011 }; // nb

    // season2021
    std::vector<double> energy_season2021 ={ 1003.5, 968.805, 980.248, 990.293 }; // MeV
    std::vector<double> xsec_season2021 = { 0.014, 0.0162, 0.0185, 0.0124 }; // nb
    std::vector<double> xsec_err_season2021 = { 0.0011, 0.0023, 0.0017, 0.0015 }; // nb

    // season2022
    std::vector<double> energy_season2022 ={ 919.966, 929.985, 934.979, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 948.727, 949.995, 950.945, 952.012, 953.003, 953.997 }; // MeV
    std::vector<double> xsec_season2022 = { 0.0038, 0.0051, 0.0036, 0.0073, 0.006, 0.0079, 0.0101, 0.0076, 0.01, 0.0105, 0.0116, 0.0104, 0.0083, 0.0084, 0.0066, 0.0106, 0.0068, 0.0049, 0.0053 }; // nb
    std::vector<double> xsec_err_season2022 = { 0.0009, 0.001, 0.0007, 0.0012, 0.0009, 0.0012, 0.0013, 0.0011, 0.0013, 0.0013, 0.0014, 0.0012, 0.0012, 0.0014, 0.0016, 0.0018, 0.0015, 0.0013, 0.0015 }; // nb
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
    
    auto hist = new TH2D("hist", "hist", 3, 910, 1010, 3, -0.005, 0.03);
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
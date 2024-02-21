#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int tot_sigma_vs_E_by_seasons()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //

    //HIGH2017
    std::vector<double> energy_HIGH2017 = {930.481, 935.478, 938.176, 938.723, 939.467, 940.166, 940.608, 941.882, 950.359}; // MeV
    std::vector<double> xsec_HIGH2017 = {-0.0003, 0.0014, 0.0119, 0.1515, 0.2312, 0.2672, 0.2941, 0.3034, 0.5472}; // nb
    std::vector<double> xsec_err_HIGH2017 = {0.0027, 0.0033, 0.004, 0.0309, 0.0355, 0.0372, 0.0392, 0.0483, 0.0979}; // nb

    //HIGH2019
    std::vector<double> energy_HIGH2019 = {936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> xsec_HIGH2019 = {0.0013, 0.394, 0.4882, 0.9989, 1.1865, 0.8842, 0.9152, 0.7781}; // nb
    std::vector<double> xsec_err_HIGH2019 = {0.0027, 0.0391, 0.0765, 0.0561, 1.0839, 0.102, 0.3919, 0.0955}; // nb

    //HIGH2020
    std::vector<double> energy_HIGH2020 = {934.705, 945.461, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> xsec_HIGH2020 = {0.0027, 0.3804, 0.4444, 0.8564, 0.7517}; // nb
    std::vector<double> xsec_err_HIGH2020 = {0.0013, 0.0198, 0.0316, 0.0605, 0.0495}; // nb

    //HIGH2021
    std::vector<double> energy_HIGH2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> xsec_HIGH2021 = {0.7173, 0.7023, 0.7077, 0.7389}; // nb
    std::vector<double> xsec_err_HIGH2021 = {0.0555, 0.0363, 0.0386, 0.007}; // nb

    //NNbar2022
    std::vector<double> energy_NNbar2022 = {919.966, 929.985, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> xsec_NNbar2022 = {0.0006, 0.0032, 0.0028, 0.0893, 0.1892, 0.2462, 0.2648, 0.2817, 0.3166, 0.3255, 0.3407, 0.3945, 0.3929, 0.4123, 0.3897, 0.4093, 0.3276}; // nb
    std::vector<double> xsec_err_NNbar2022 = {0.0011, 0.0013, 0.0012, 0.0097, 0.0146, 0.0159, 0.016, 0.0169, 0.0178, 0.0176, 0.0173, 0.0182, 0.0387, 0.1618, 0.052, 0.1054, 0.0856}; // nb

    // ********************* End of Data ********************* //


    //HIGH2017
    TGraphErrors xsec_vs_energy_HIGH2017(energy_HIGH2017.size(), energy_HIGH2017.data(), xsec_HIGH2017.data(), 
                                            zeroes.data(), xsec_err_HIGH2017.data());
    xsec_vs_energy_HIGH2017.GetXaxis()->SetLimits(915, 1010);
    xsec_vs_energy_HIGH2017.GetYaxis()->SetLimits(-0.1, 5);
    xsec_vs_energy_HIGH2017.SetMarkerColor(1);
    xsec_vs_energy_HIGH2017.SetName("xsec_vs_energy_HIGH2017");
    xsec_vs_energy_HIGH2017.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_HIGH2017.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_HIGH2017.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} both types of events");

    //HIGH2019
    TGraphErrors xsec_vs_energy_HIGH2019(energy_HIGH2019.size(), energy_HIGH2019.data(), xsec_HIGH2019.data(), 
                                            zeroes.data(), xsec_err_HIGH2019.data());
    xsec_vs_energy_HIGH2019.GetXaxis()->SetLimits(915, 1010);
    xsec_vs_energy_HIGH2019.GetYaxis()->SetLimits(-0.1, 5);
    xsec_vs_energy_HIGH2019.SetMarkerColor(2);
    xsec_vs_energy_HIGH2019.SetName("xsec_vs_energy_HIGH2019");
    xsec_vs_energy_HIGH2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_HIGH2019.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_HIGH2019.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} both types of events");

    //HIGH2020
    TGraphErrors xsec_vs_energy_HIGH2020(energy_HIGH2020.size(), energy_HIGH2020.data(), xsec_HIGH2020.data(), 
                                            zeroes.data(), xsec_err_HIGH2020.data());
    xsec_vs_energy_HIGH2020.GetXaxis()->SetLimits(915, 1010);
    xsec_vs_energy_HIGH2020.GetYaxis()->SetLimits(-0.1, 5);
    xsec_vs_energy_HIGH2020.SetMarkerColor(3);
    xsec_vs_energy_HIGH2020.SetName("xsec_vs_energy_HIGH2020");
    xsec_vs_energy_HIGH2020.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_HIGH2020.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_HIGH2020.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} both types of events");

    //HIGH2021
    TGraphErrors xsec_vs_energy_HIGH2021(energy_HIGH2021.size(), energy_HIGH2021.data(), xsec_HIGH2021.data(), 
                                            zeroes.data(), xsec_err_HIGH2021.data());
    xsec_vs_energy_HIGH2021.GetXaxis()->SetLimits(915, 1010);
    xsec_vs_energy_HIGH2021.GetYaxis()->SetLimits(-0.1, 5);
    xsec_vs_energy_HIGH2021.SetMarkerColor(4);
    xsec_vs_energy_HIGH2021.SetName("xsec_vs_energy_HIGH2021");
    xsec_vs_energy_HIGH2021.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_HIGH2021.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_HIGH2021.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} both types of events");

    //NNbar2022
    TGraphErrors xsec_vs_energy_NNbar2022(energy_NNbar2022.size(), energy_NNbar2022.data(), xsec_NNbar2022.data(), 
                                            zeroes.data(), xsec_err_NNbar2022.data());
    xsec_vs_energy_NNbar2022.GetXaxis()->SetLimits(915, 1010);
    xsec_vs_energy_NNbar2022.GetYaxis()->SetLimits(-0.1, 5);
    xsec_vs_energy_NNbar2022.SetMarkerColor(65);
    xsec_vs_energy_NNbar2022.SetName("xsec_vs_energy_NNbar2022");
    xsec_vs_energy_NNbar2022.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_NNbar2022.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_NNbar2022.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} both types of events");


    xsec_vs_energy_HIGH2017.DrawClone("AP");
    xsec_vs_energy_HIGH2019.DrawClone("P same");
    xsec_vs_energy_HIGH2020.DrawClone("P same");
    xsec_vs_energy_HIGH2021.DrawClone("P same");
    xsec_vs_energy_NNbar2022.DrawClone("P same");

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Seasons","C"); // option "C" allows to center the header

    legend->AddEntry("xsec_vs_energy_HIGH2017","HIGH2017","ep");
    legend->AddEntry("xsec_vs_energy_HIGH2019","HIGH2019","ep");
    legend->AddEntry("xsec_vs_energy_HIGH2020","HIGH2020","ep");
    legend->AddEntry("xsec_vs_energy_HIGH2021","HIGH2021","ep");
    legend->AddEntry("xsec_vs_energy_NNbar2022","NNbar2022","ep");
    legend->DrawClone();

    canv.DrawClone();
    return 0;
}
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

    //HIGH2019
    std::vector<double> energy_HIGH2019 = {936.305, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> xsec_HIGH2019 = {0.0052, 7.2206, 0.9989, 1.1865, 0.8842, 0.9152, 0.7781}; // nb
    std::vector<double> xsec_err_HIGH2019 = {0.0017, 3.1771, 0.0561, 1.0839, 0.102, 0.3919, 0.0955}; // nb

    //HIGH2020
    std::vector<double> energy_HIGH2020 = {934.705, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> xsec_HIGH2020 = {0.0022, 3.1314, 0.8564, 0.7517}; // nb
    std::vector<double> xsec_err_HIGH2020 = {0.0005, 0.5369, 0.0605, 0.0495}; // nb

    //HIGH2021
    std::vector<double> energy_HIGH2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> xsec_HIGH2021 = {0.7173, 0.7023, 0.7077, 0.7389}; // nb
    std::vector<double> xsec_err_HIGH2021 = {0.0555, 0.0363, 0.0386, 0.007}; // nb

    //NNbar2022
    std::vector<double> energy_NNbar2022 = {919.966, 929.985, 937.505, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> xsec_NNbar2022 = {0.0041, 0.003, 0.0032, 48.9151, 1.4853, 3.4112, 2.1058, 1.5605}; // nb
    std::vector<double> xsec_err_NNbar2022 = {0.0006, 0.0005, 0.0006, 11.5101, 0.4465, 0.3195, 0.7074, 0.3582}; // nb

    // ********************* End of Data ********************* //


    //HIGH2019
    TGraphErrors xsec_vs_energy_HIGH2019(energy_HIGH2019.size(), energy_HIGH2019.data(), xsec_HIGH2019.data(), 
                                            zeroes.data(), xsec_err_HIGH2019.data());
    xsec_vs_energy_HIGH2019.GetXaxis()->SetLimits(915, 1010);
    xsec_vs_energy_HIGH2019.GetYaxis()->SetLimits(-0.1, 5);
    xsec_vs_energy_HIGH2019.SetMarkerColor(1);
    xsec_vs_energy_HIGH2019.SetName("xsec_vs_energy_HIGH2019");
    xsec_vs_energy_HIGH2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_HIGH2019.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_HIGH2019.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} collinear events");

    //HIGH2020
    TGraphErrors xsec_vs_energy_HIGH2020(energy_HIGH2020.size(), energy_HIGH2020.data(), xsec_HIGH2020.data(), 
                                            zeroes.data(), xsec_err_HIGH2020.data());
    xsec_vs_energy_HIGH2020.GetXaxis()->SetLimits(915, 1010);
    xsec_vs_energy_HIGH2020.GetYaxis()->SetLimits(-0.1, 5);
    xsec_vs_energy_HIGH2020.SetMarkerColor(2);
    xsec_vs_energy_HIGH2020.SetName("xsec_vs_energy_HIGH2020");
    xsec_vs_energy_HIGH2020.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_HIGH2020.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_HIGH2020.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} collinear events");

    //HIGH2021
    TGraphErrors xsec_vs_energy_HIGH2021(energy_HIGH2021.size(), energy_HIGH2021.data(), xsec_HIGH2021.data(), 
                                            zeroes.data(), xsec_err_HIGH2021.data());
    xsec_vs_energy_HIGH2021.GetXaxis()->SetLimits(915, 1010);
    xsec_vs_energy_HIGH2021.GetYaxis()->SetLimits(-0.1, 5);
    xsec_vs_energy_HIGH2021.SetMarkerColor(3);
    xsec_vs_energy_HIGH2021.SetName("xsec_vs_energy_HIGH2021");
    xsec_vs_energy_HIGH2021.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_HIGH2021.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_HIGH2021.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} collinear events");

    //NNbar2022
    TGraphErrors xsec_vs_energy_NNbar2022(energy_NNbar2022.size(), energy_NNbar2022.data(), xsec_NNbar2022.data(), 
                                            zeroes.data(), xsec_err_NNbar2022.data());
    xsec_vs_energy_NNbar2022.GetXaxis()->SetLimits(915, 1010);
    xsec_vs_energy_NNbar2022.GetYaxis()->SetLimits(-0.1, 5);
    xsec_vs_energy_NNbar2022.SetMarkerColor(4);
    xsec_vs_energy_NNbar2022.SetName("xsec_vs_energy_NNbar2022");
    xsec_vs_energy_NNbar2022.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_NNbar2022.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_NNbar2022.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} collinear events");


    xsec_vs_energy_HIGH2019.DrawClone("AP");
    xsec_vs_energy_HIGH2020.DrawClone("P same");
    xsec_vs_energy_HIGH2021.DrawClone("P same");
    xsec_vs_energy_NNbar2022.DrawClone("P same");

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Seasons","C"); // option "C" allows to center the header

    legend->AddEntry("xsec_vs_energy_HIGH2019","HIGH2019","ep");
    legend->AddEntry("xsec_vs_energy_HIGH2020","HIGH2020","ep");
    legend->AddEntry("xsec_vs_energy_HIGH2021","HIGH2021","ep");
    legend->AddEntry("xsec_vs_energy_NNbar2022","NNbar2022","ep");
    legend->DrawClone();

    canv.DrawClone();
    return 0;
}
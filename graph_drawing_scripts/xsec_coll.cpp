#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>

int xsec_coll()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);

    // ********************* Start of Data ********************* //
    std::vector<double> energy = {949.995, 950.15, 950.29, 950.945, 952.012, 953.003, 953.997, 956.084, 960.252, 962.687, 968.805, 970.583, 972.917, 977.158, 980.248, 987.81, 990.293, 1003.5}; // MeV
    std::vector<double> xsec = {48.2519, 5.9777, 2.7865, 1.4444, 3.4112, 2.3911, 1.5605, 1.0132, 0.903, 1.0961, 0.7453, 0.7464, 0.7713, 0.8516, 0.7348, 0.7373, 0.6811, 0.7647}; // nb
    std::vector<double> xsec_err = {42.6145, 6.4979, 2.5859, 1.4203, 3.3825, 2.4344, 1.8059, 0.7832, 0.3777, 0.743, 0.2419, 0.225, 0.2811, 0.7229, 0.1883, 0.2462, 0.1486, 0.1774}; // nb
    // ********************* End of Data ********************* //

    // season2019
    TGraphErrors xsec_vs_energy(energy.size(), energy.data(), xsec.data(), zeroes.data(), xsec_err.data());
    xsec_vs_energy.SetMarkerColor(kRed);
    xsec_vs_energy.SetName("xsec_vs_energy");
    xsec_vs_energy.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy.GetYaxis()->SetTitle("#sigma^{(vis)}_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} collinear events");

    xsec_vs_energy.DrawClone("AP");
    canv.DrawClone();
    return 0;
}
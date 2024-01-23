#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int tot_sigma_vs_E()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //

    std::vector<double> energy = {930.481, 935.478, 938.176, 938.723, 939.467, 940.166, 940.608, 941.882, 950.359,// 2017
                                936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81, // 2019
                                934.705, 945.461, 950.29, 960.252, 970.583, //2020
                                968.805, 980.248, 990.293, 1003.5, // 2021
                                919.966, 929.985, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV 2022

    std::vector<double> xsec = {0.0002, 0.003, 0.0122, 0.3494, 0.4567, 0.5616, 0.675, 0.709, 0.8921, // 2017
                                -0.0005, 0.7852, 1.2028, 0.9989, 1.1865, 0.8842, 0.9152, 0.7781, // 2019
                                0.0009, 0.8201, 0.9628, 0.8564, 0.7517, // 2020
                                0.7173, 0.7023, 0.7077, 0.7604, // 2021
                                -0.0001, 0.0022, 0.0018, 0.5277, 0.3874, 0.5496, 0.5941, 0.6222, 0.6919, 0.7141, 0.7584, 0.8164, 0.7973, 0.8652, 0.7395, 0.7784, 0.768}; // nb 2022

    std::vector<double> xsec_err = {0.0019, 0.0033, 0.0034, 0.0941, 0.1158, 0.1369, 0.1551, 0.1717, 0.3029, //2017
                                    0.0018, 0.1698, 0.2994, 0.0561, 1.0839, 0.102, 0.3919, 0.0955, //2019
                                    0.0009, 0.1621, 0.5948, 0.0605, 0.0495, // 2020
                                    0.0555, 0.0363, 0.0386, 0.0298, // 2021
                                    0.0007, 0.001, 0.0009, 0.1638, 0.0807, 0.1111, 0.1189, 0.1252, 0.1382, 0.142, 0.1512, 0.1639, 0.5915, 0.8157, 0.2123, 0.4912, 0.421}; // nb 2022

    // ********************* End of Data ********************* //

    // season2017
    TGraphErrors xsec_vs_energy(energy.size(), energy.data(), xsec.data(), zeroes.data(), xsec_err.data());
    xsec_vs_energy.SetName("xsec_vs_energy");
    xsec_vs_energy.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy.SetTitle("Both types of events");

    xsec_vs_energy.DrawClone("AP");

    canv.DrawClone();
    return 0;
}
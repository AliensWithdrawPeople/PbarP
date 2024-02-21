# Results

chi2/ndf = 77/39
Fit function:
E < threshold: 0;
threshold < Energy < 1.91: level_stars (1 - exp(-slope( Energy - threshold)));
E > 1.91 GeV: level
minimum:
  Valid         : yes
  Function calls: 486
  Minimum value : 77.0211893
  Edm           : 1.047837305e-05
  Internal parameters:
         1.871168
     0.8323622195
      129.7378689
     0.5268693187
  Covariance matrix:
  5.5357065e-06  4.1948428e-07     0.11977362 -6.9493497e-05
  4.1948428e-07  5.5506901e-05    0.011203504 -9.7609498e-06
     0.11977362    0.011203504       2755.438     -1.7287716
 -6.9493497e-05 -9.7609498e-06     -1.7287716   0.0012564603

  External parameters:
  Pos |    Name    |  type   |      Value       |    Error +/-
    0 |  threshold |  free   |         1.871168 | 0.002352808221
    1 |      level |  free   |     0.8323622195 | 0.007450295371
    2 |      slope |  free   |      129.7378689 |  52.49226564
    3 | level_stars |  free   |     0.5268693187 | 0.03544658317

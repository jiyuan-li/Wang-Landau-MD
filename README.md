# Wang-Landau-MD
#1. What this code is used for?

Implemented Wang-Landau method into molecular dynamics (MD) simulations to enable efficient multicanonical MD simulations for systems with ruggeed potential surfaces such as protein.  

#2. Why implementing Wang-Landau into MD, which is much harder than into MC, is necessary? 

1) for liquid simulations, the sampling efficiency of the MC method is comparable, or sometimes superior to MD. for protein simulations, however, MD shows about 1.5 times better sampling efficiency. This difference is attributed to the inertia force term in MD, which does not exist in MC. 2) this implentation is part of SAGES (Suite for Advanced Generalized Ensemble Simulations).

#3 Algorithms referred to:
1) Nagasima et al. Physical Review E 75, 066706 (2007)
2) Wang and Landau, Phys. Rev. E 64, 056101 (2001)

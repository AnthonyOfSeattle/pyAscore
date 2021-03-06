import unittest
import time
import os
import pickle
import numpy as np
from pyascore import PyAscore

class TestPyAscore(unittest.TestCase):
    def test_single_spectrum_score(self):
        ascore = PyAscore(bin_size=100., n_top=10,
                          mod_group="STY", mod_mass=79.966331)
        def test_match_pairs(match_file, spec_file):
            with open(os.path.join("test", "match_spectra_pairs", match_file), "rb") as src:
                match_list = pickle.load(src)

            with open(os.path.join("test", "match_spectra_pairs", spec_file), "rb") as src:
                spectra_list = pickle.load(src)

            n = 0
            running_time = 0
            for match, spectra in zip(match_list, spectra_list):
                running_time -= time.time()
                ascore = PyAscore(bin_size=100., n_top=10,
                                  mod_group="STY", mod_mass=79.966331)
                ascore.score(spectra["mz_values"], 
                             spectra["intensity_values"], 
                             match["peptide"], 
                             len(match["mod_positions"]))
                running_time += time.time()
                n += 1

            print("Average for ({}, {}): {} sec/match".format( 
                match_file, spec_file, (running_time/n) )
            )

            n = 0
            running_time = 0
            for match, spectra in zip(match_list, spectra_list):
                running_time -= time.time()
                ascore = PyAscore(bin_size=100., n_top=10,
                                  mod_group="STY", mod_mass=79.966331)
                ascore.add_neutral_loss("ST", 18.01528)
                ascore.score(spectra["mz_values"],
                             spectra["intensity_values"],
                             match["peptide"],
                             len(match["mod_positions"]))
                running_time += time.time()
                n += 1

            print("Average with neutral loss for ({}, {}): {} sec/match".format(
                match_file, spec_file, (running_time/n) )
            )
            print()

        test_match_pairs("velos_matches_1_mods.pkl", "velos_spectra_1_mods.pkl")
        test_match_pairs("velos_matches_2_mods.pkl", "velos_spectra_2_mods.pkl")
        test_match_pairs("velos_matches_3_mods.pkl", "velos_spectra_3_mods.pkl")
        test_match_pairs("dump_match.pkl", "dump_spectra.pkl")
        test_match_pairs("velos_matches_aux.pkl", "velos_spectra_aux.pkl")

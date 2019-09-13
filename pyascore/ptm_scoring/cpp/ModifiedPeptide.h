#ifndef MODIFIEDPEPTIDE_H
#define MODIFIEDPEPTIDE_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Types.h"

namespace ptmscoring {

    class ModifiedPeptide {
        std::string mod_group;
        float mod_mass;

        std::string peptide;
        size_t n_of_mod;
        std::vector<size_t> modifiable;
        std::unordered_map<size_t, size_t> signature;

        std::vector<std::vector<float>> residues;
        std::vector<float> fragments;
        std::unordered_map<float, std::vector<size_t>> fragment_scores;

        char fragment_type;
        size_t fragment_ind;
        std::vector<float> running_sum;
        std::string running_sequence;
        void calculateFragment(size_t);

        void initializeResidues();
        void applyAuxMods(const size_t * = NULL, const float * = NULL, size_t = 0);
        void initializeFragments();
        public:
            ModifiedPeptide(std::string, float);
            ~ModifiedPeptide();

            void consumePeptide(std::string, size_t, 
                                const size_t * = NULL, 
                                const float * = NULL, 
                                size_t = 0);
            void consumePeak(float, size_t);

            std::string getModGroup() const;
            float getModMass() const;

            size_t resetIterator(char);
            size_t incrSignature();
            std::vector<size_t> getSignature();
            size_t incrFragment();
            char getFragmentType();
            float getFragmentMZ(size_t);
            size_t getFragmentSize();
            std::string getFragmentSeq();

            class FragmentGraph;
            FragmentGraph getFragmentGraph(char, size_t);
    };

    class ModifiedPeptide::FragmentGraph {
        // Information that is abstracted away from user
        const ModifiedPeptide * modified_peptide;
        size_t residue_ind;
        void resetResidueInd();
        void incrResidueInd();
        bool isResidueEnd();
        size_t getResidueDistance();

        // Information made public
        char fragment_type;
        size_t charge_state;

        size_t n_mods_outstanding;
        std::vector<size_t> modifiable;
        std::unordered_map<size_t, size_t> signature;

        std::vector<float> running_sum;
        std::string running_sequence;
        void calculateFragment();
        public:
            FragmentGraph(const ModifiedPeptide *, char, size_t);
            ~FragmentGraph();

            char getFragmentType();
            size_t getChargeState();

            void resetIterator();
            void incrSignature();
            bool isSignatureEnd();
            void incrFragment();
            bool isFragmentEnd();

            std::vector<size_t> getSignature();
            float getFragmentMZ();
            size_t getFragmentSize();
            std::string getFragmentSeq();
    };


}

#endif

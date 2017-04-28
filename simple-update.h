//The following ifndef/define/endif pattern is called a 
//scope guard, and prevents the C++ compiler (actually, preprocessor)
//from including a header file more than once.
#ifndef __SMPL_UPDT_H_
#define __SMPL_UPDT_H_

#include <cmath>
#include "su2.h"
#include "ctm-cluster.h"
#include "ctm-cluster-global.h"

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wunused-result"
#include "itensor/all.h"
#pragma GCC diagnostic pop


/*
 * H_J1J2 acting on a square lattice can be decomposed into sum of
 * 
 * of 8 terms, each one consisting of a sum of terms as
 *
 * H_123 = J1(S_1.S_2 + S_2.S_3) + 2*J2(S_1.S_3)
 * 
 * acting along 2 links attached to a same site + diagonal.
 * This can be seen by trying to "cover" all interactions == links
 * between sites given by terms S_i.S_j, where i,j denotes NN or NNN sites,
 * by triangles. The additional factor of 2 in front of J2 is due to 
 * double counting NN links in such coverings.
 * Taking 2x2 unit cell with 4 inequivalent sites (tensors):
 *
 *     |    |
 *  -- A -- B --
 *     |    |
 *  -- D -- C --
 *     |    |
 * 
 * There are 4 possible triplets of sites over which H_123 can act by 
 * substituing 123 with respective sites. These are ABC, BCD, CDA and DAB 
 * (flip of the order ABC == CBA, due to symmetry of interaction terms).
 *  
 * Exponential of H_123 can be expressed as a matrix product operator
 * and then used to perform "simple update" of on-site tensors A,B,C,D
 *
 *    \ |    _____           \ |    ___             |
 *   --|A|~~|     |~~       --|A|~~|H_A|~~      --|A~|-- 
 *    \ |   |     |    ==>   \ |     |      ==     ||
 *   --|B|~~|H_ABC|~~  ==>  --|B|~~|H_B|~~  ==  --|B~|--
 *    \ |   |     |    ==>   \ |     |      ==     ||
 *   --|C|~~|_____|~~       --|C|~~|H_C|~~      --|C~|--  
 *      |                      |                    |
 *
 */

/*
 * this struct holds instance of particular 3-site MPO composed
 * by three tensors
 *
 *    s1'              s2'              s3'
 *    |                |                | 
 *   |H1|--I_MPO3s12--|H2|--I_MPO3s23--|H3|
 *    |                |                | 
 *    s1               s2               s3
 *
 * exposing the physical indices s1,s2,s3
 *
 */

// Index names of 3-site MPO indices
const std::string TAG_MPO3S_PHYS1 = "I_MPO3S_S1";
const std::string TAG_MPO3S_PHYS2 = "I_MPO3S_S2";
const std::string TAG_MPO3S_PHYS3 = "I_MPO3S_S3";
const std::string TAG_MPO3S_12LINK = "I_MPO3S_L12";
const std::string TAG_MPO3S_23LINK = "I_MPO3S_L23";

// types for auxiliary indices of MPO tensors
const auto MPOLINK = itensor::IndexType(TAG_IT_MPOLINK);

struct MPO_3site {
	itensor::ITensor H1, H2, H3;

	// expose physical indices
	itensor::Index Is1, Is2, Is3;
};

/*
 * Define multiplication of 3site MPO by REAL scalar scalar*MPO_3site
 *
 */
MPO_3site operator*(double scalar, MPO_3site const& mpo3s);

typedef enum ID_TYPE {
    ID_TYPE_1,
    ID_TYPE_2
} id_type;

// string to enum conversion
ID_TYPE toID_TYPE(std::string const& idType);

/*
 * construct Identity MPO_3site 
 *
 */
// Splits SVD values S^1/2 : S^1/4 : S^1/4
MPO_3site getMPO3s_Id(int physDim);

// Splits SVD values S^1/3 : S^1/3 : S^1/3
MPO_3site getMPO3s_Id_v2(int physDim);

typedef enum F_MPO3S {
    F_MPO3S_1,
    F_MPO3S_2,
    F_MPO3S_3,
    F_MPO3S_4,
    F_MPO3S_5,
    F_MPO3S_6
} f_mpo3s;

// string to enum conversion
F_MPO3S toF_MPO3S(std::string const& fMpo3s);

/*
 * Apply MPO_3site over three sites ABC
 *
 */
void applyH_123(MPO_3site const& mpo3s, 
	itensor::ITensor & T1, itensor::ITensor & T2, itensor::ITensor & T3, 
	std::pair<itensor::Index, itensor::Index> const& link12,
	std::pair<itensor::Index, itensor::Index> const& link23);

void applyH_123_v2(MPO_3site const& mpo3s, 
	itensor::ITensor & T1, itensor::ITensor & T2, itensor::ITensor & T3, 
	std::pair<itensor::Index, itensor::Index> const& link12,
	std::pair<itensor::Index, itensor::Index> const& link23);

void applyH_123_v3(MPO_3site const& mpo3s, 
	itensor::ITensor & T1, itensor::ITensor & T2, itensor::ITensor & T3, 
	std::pair<itensor::Index, itensor::Index> const& link12,
	std::pair<itensor::Index, itensor::Index> const& link23);

void applyH_123_v4(MPO_3site const& mpo3s, 
	itensor::ITensor & T1, itensor::ITensor & T2, itensor::ITensor & T3, 
	std::pair<itensor::Index, itensor::Index> const& link12,
	std::pair<itensor::Index, itensor::Index> const& link23);

void applyH_123_v5(MPO_3site const& mpo3s, 
	itensor::ITensor & T1, itensor::ITensor & T2, itensor::ITensor & T3, 
	std::pair<itensor::Index, itensor::Index> const& link12,
	std::pair<itensor::Index, itensor::Index> const& link23);

void applyH_123_v6(MPO_3site const& mpo3s, 
	itensor::ITensor & T1, itensor::ITensor & T2, itensor::ITensor & T3, 
	std::pair<itensor::Index, itensor::Index> const& link12,
	std::pair<itensor::Index, itensor::Index> const& link23);

std::ostream& 
operator<<(std::ostream& s, MPO_3site const& mpo3s);

#endif
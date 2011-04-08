/* tests/test-hybrid-vector.C
 * Copyright 2010 Bradford Hovinen
 * Written by Bradford Hovinen <hovinen@gmail.com>
 *
 * ---------------------------------------------------------
 *
 * See COPYING for license information.
 *
 * Test for hybrid sparse-dense vector-format
 */

#include <iostream>

#include "test-common.h"

#include "linbox/field/gf2.h"
#include "linbox/vector/vector-domain.h"
#include "linbox/vector/sparse-subvector-hybrid.h"

using namespace LinBox;

typedef GF2 Field;

bool testAdd ()
{
	commentator.start ("Testing VD.add", __FUNCTION__);

	std::ostream &report = commentator.report (Commentator::LEVEL_NORMAL, INTERNAL_DESCRIPTION);
	std::ostream &error = commentator.report (Commentator::LEVEL_IMPORTANT, INTERNAL_ERROR);

	bool pass = true;

	Field F (2);
	VectorDomain<Field> VD (F);

	Vector<GF2>::Hybrid u, v, w, t;

	// Test 1: Indices in same block
	u.clear ();
	v.clear ();
	t.clear ();

	u.push_back (Vector<GF2>::Hybrid::value_type (0, 1));
	v.push_back (Vector<GF2>::Hybrid::value_type (0, 1 | (1 << 1)));
	t.push_back (Vector<GF2>::Hybrid::value_type (0, 1 << 1));

	VD.add (w, u, v);

	report << "Test 1:" << std::endl;
	report << "    u = ";
	VD.write (report, u) << std::endl;
	report << "    v = ";
	VD.write (report, v) << std::endl;
	report << "u + v = ";
	VD.write (report, w) << std::endl;
	report << "    t = ";
	VD.write (report, t) << std::endl;

	if (!VD.areEqual (w, t)) {
		error << "ERROR (Test 1): VectorDomain reports u + v != t" << std::endl;
		pass = false;
	}

	// Test 2: Indices in different blocks, u before v
	u.clear ();
	v.clear ();
	t.clear ();

	u.push_back (Vector<GF2>::Hybrid::value_type (0, 1));
	v.push_back (Vector<GF2>::Hybrid::value_type (1, 1));
	t.push_back (Vector<GF2>::Hybrid::value_type (0, 1));
	t.push_back (Vector<GF2>::Hybrid::value_type (1, 1));

	VD.add (w, u, v);

	report << "Test 2:" << std::endl;
	report << "    u = ";
	VD.write (report, u) << std::endl;
	report << "    v = ";
	VD.write (report, v) << std::endl;
	report << "u + v = ";
	VD.write (report, w) << std::endl;
	report << "    t = ";
	VD.write (report, t) << std::endl;

	if (!VD.areEqual (w, t)) {
		error << "ERROR (Test 2): VectorDomain reports u + v != t" << std::endl;
		pass = false;
	}

	// Test 3: Indices in different blocks, v before u
	u.clear ();
	v.clear ();
	t.clear ();

	u.push_back (Vector<GF2>::Hybrid::value_type (1, 1));
	v.push_back (Vector<GF2>::Hybrid::value_type (0, 1));
	t.push_back (Vector<GF2>::Hybrid::value_type (0, 1));
	t.push_back (Vector<GF2>::Hybrid::value_type (1, 1));

	VD.add (w, u, v);

	report << "Test 3:" << std::endl;
	report << "    u = ";
	VD.write (report, u) << std::endl;
	report << "    v = ";
	VD.write (report, v) << std::endl;
	report << "u + v = ";
	VD.write (report, w) << std::endl;
	report << "    t = ";
	VD.write (report, t) << std::endl;

	if (!VD.areEqual (w, t)) {
		error << "ERROR (Test 3): VectorDomain reports u + v != t" << std::endl;
		pass = false;
	}

	// Test 4: u = 0
	u.clear ();
	v.clear ();
	t.clear ();

	v.push_back (Vector<GF2>::Hybrid::value_type (0, 1));
	t.push_back (Vector<GF2>::Hybrid::value_type (0, 1));

	VD.add (w, u, v);

	report << "Test 4:" << std::endl;
	report << "    u = ";
	VD.write (report, u) << std::endl;
	report << "    v = ";
	VD.write (report, v) << std::endl;
	report << "u + v = ";
	VD.write (report, w) << std::endl;
	report << "    t = ";
	VD.write (report, t) << std::endl;

	if (!VD.areEqual (w, t)) {
		error << "ERROR (Test 4): VectorDomain reports u + v != t" << std::endl;
		pass = false;
	}

	// Test 5: v = 0
	u.clear ();
	v.clear ();
	t.clear ();

	u.push_back (Vector<GF2>::Hybrid::value_type (0, 1));
	t.push_back (Vector<GF2>::Hybrid::value_type (0, 1));

	VD.add (w, u, v);

	report << "Test 5:" << std::endl;
	report << "    u = ";
	VD.write (report, u) << std::endl;
	report << "    v = ";
	VD.write (report, v) << std::endl;
	report << "u + v = ";
	VD.write (report, w) << std::endl;
	report << "    t = ";
	VD.write (report, t) << std::endl;

	if (!VD.areEqual (w, t)) {
		error << "ERROR (Test 5): VectorDomain reports u + v != t" << std::endl;
		pass = false;
	}

	// Test 6: u, v have lengths longer than 1
	u.clear ();
	v.clear ();
	t.clear ();

	u.push_back (Vector<GF2>::Hybrid::value_type (0, 2ULL));
	u.push_back (Vector<GF2>::Hybrid::value_type (1, 1ULL));

	v.push_back (Vector<GF2>::Hybrid::value_type (0, 4ULL));
	v.push_back (Vector<GF2>::Hybrid::value_type (1, 1ULL));

	t.push_back (Vector<GF2>::Hybrid::value_type (0, 2 | 4));

	VD.add (w, u, v);

	report << "Test 6:" << std::endl;
	report << "    u = ";
	VD.write (report, u) << std::endl;
	report << "    v = ";
	VD.write (report, v) << std::endl;
	report << "u + v = ";
	VD.write (report, w) << std::endl;
	report << "    t = ";
	VD.write (report, t) << std::endl;

	if (!VD.areEqual (w, t)) {
		error << "ERROR (Test 6): VectorDomain reports u + v != t" << std::endl;
		pass = false;
	}

	commentator.stop (MSG_STATUS (pass));

	return pass;
}

bool testFirstNonzeroEntry ()
{
	commentator.start ("Testing VD.firstNonzeroEntry", __FUNCTION__);

	std::ostream &error = commentator.report (Commentator::LEVEL_IMPORTANT, INTERNAL_ERROR);

	bool pass = true;

	Field F (2);
	VectorDomain<Field> VD (F);

	bool a;

	Vector<GF2>::Hybrid v;

	int idx;

	v.push_back (Vector<GF2>::Hybrid::value_type (2, Vector<GF2>::Hybrid::Endianness::e_j (0)));

	idx = VD.firstNonzeroEntry (a, v);

	if (idx != 2 * WordTraits<Vector<GF2>::Hybrid::word_type>::bits) {
		error << "ERROR (Test 1): VD.firstNonzeroEntry (a, v) = " << idx
		      << " (should be " << 2 * 8 * sizeof (Vector<GF2>::Hybrid::word_type) << ")" << std::endl;
		pass = false;
	}

	v.clear ();

	v.push_back (Vector<GF2>::Hybrid::value_type (2, Vector<GF2>::Hybrid::Endianness::e_j (WordTraits<Vector<GF2>::Hybrid::word_type>::bits / 2)));

	idx = VD.firstNonzeroEntry (a, v);

	if (idx != 5 * WordTraits<Vector<GF2>::Hybrid::word_type>::bits / 2) {
		error << "ERROR (Test 2): VD.firstNonzeroEntry (a, v) = " << idx
		      << " (should be " << 2 * 8 * sizeof (Vector<GF2>::Hybrid::word_type) + 16 << ")" << std::endl;
		pass = false;
	}

	v.clear ();

	v.push_back (Vector<GF2>::Hybrid::value_type (3, Vector<GF2>::Hybrid::Endianness::e_j (WordTraits<Vector<GF2>::Hybrid::word_type>::bits - 1)));

	idx = VD.firstNonzeroEntry (a, v);

	if (idx != 3 * WordTraits<Vector<GF2>::Hybrid::word_type>::bits + (WordTraits<Vector<GF2>::Hybrid::word_type>::bits - 1)) {
		error << "ERROR (Test 3): VD.firstNonzeroEntry (a, v) = " << idx
		      << " (should be " << 3 * 8 * sizeof (Vector<GF2>::Hybrid::word_type) + (8 * sizeof (Vector<GF2>::Hybrid::word_type) - 1) << ")" << std::endl;
		pass = false;
	}

	commentator.stop (MSG_STATUS (pass));

	return pass;
}

Vector<GF2>::Hybrid::word_type connect (Vector<GF2>::Hybrid::word_type word1, Vector<GF2>::Hybrid::word_type word2, int shift) 
{
	if (shift == 0)
		return word1;
	else
		return Vector<GF2>::Hybrid::Endianness::shift_left (word1, shift) | Vector<GF2>::Hybrid::Endianness::shift_right (word2, WordTraits<Vector<GF2>::Hybrid::word_type>::bits - shift);
}

bool testSparseSubvectorHybrid ()
{
	commentator.start ("Testing SparseSubvector<Hybrid>", __FUNCTION__);

	std::ostream &report = commentator.report (Commentator::LEVEL_NORMAL, INTERNAL_DESCRIPTION);
	std::ostream &error = commentator.report (Commentator::LEVEL_IMPORTANT, INTERNAL_ERROR);

	bool pass = true;

	Vector<GF2>::Hybrid v;

	Vector<GF2>::Hybrid::word_type pattern[2] = { 0xf0f0f0f0f0f0f0f0ULL, 0xaaaaaaaaaaaaaaaaULL };
	Vector<GF2>::Hybrid::word_type check;

	uint16 offset = 5;
	uint16 len = WordTraits<Vector<GF2>::Hybrid::word_type>::bits + 4;

	report << "Test 1" << std::endl;

	v.push_back (Vector<GF2>::Hybrid::value_type (0, pattern[0]));
	v.push_back (Vector<GF2>::Hybrid::value_type (1, pattern[1]));

	SparseSubvector<Vector<GF2>::Hybrid, VectorCategories::HybridZeroOneVectorTag> v1 (v, offset, offset + len);

	SparseSubvector<Vector<GF2>::Hybrid, VectorCategories::HybridZeroOneVectorTag>::const_iterator i_v1 = v1.begin ();

	if (i_v1->first != 0) {
		error << "ERROR: First index should be 0, is " << std::dec << i_v1->first << std::endl;
		pass = false;
	}

	check = connect (pattern[0], pattern[1], offset);

	if (i_v1->second != check) {
		error << "ERROR: First word should be " << std::hex << static_cast<uint64> (check) << ", is " << std::hex << static_cast<uint64> (i_v1->second) << std::endl;
		pass = false;
	}

	++i_v1;

	if (i_v1->first != 1) {
		error << "ERROR: Second index should be 1, is " << std::dec << i_v1->first << std::endl;
		pass = false;
	}

	check = connect (pattern[1], 0ULL, offset) & Vector<GF2>::Hybrid::Endianness::mask_left (len % WordTraits<Vector<GF2>::Hybrid::word_type>::bits);

	if (i_v1->second != check) {
		error << "ERROR: Second word should be " << std::hex << static_cast<uint64> (check) << ", is " << std::hex << static_cast<uint64> (i_v1->second) << std::endl;
		pass = false;
	}

	++i_v1;

	if (i_v1 != v1.end ()) {
		error << "ERROR: Did not hit end when expected." << std::endl;
		pass = false;
	}

	v.clear ();

	report << "Test 2" << std::endl;

	v.push_back (Vector<GF2>::Hybrid::value_type (1, pattern[0]));

	SparseSubvector<Vector<GF2>::Hybrid, VectorCategories::HybridZeroOneVectorTag> v2 (v, offset, offset + len);

	SparseSubvector<Vector<GF2>::Hybrid, VectorCategories::HybridZeroOneVectorTag>::const_iterator i_v2 = v2.begin ();

	if (i_v2->first != 0) {
		error << "ERROR: First index should be 0, is " << std::dec << i_v2->first << std::endl;
		pass = false;
	}

	check = connect (0ULL, pattern[0], offset);

	if (i_v2->second != check) {
		error << "ERROR: First word should be " << std::hex << static_cast<uint64> (check) << ", is " << std::hex << static_cast<uint64> (i_v2->second) << std::endl;
		pass = false;
	}

	++i_v2;

	if (i_v2 == v2.end ()) {
		error << "ERROR: Iterator ended prematurely." << std::endl;
		pass = false;
	}

	if (i_v2->first != 1) {
		error << "ERROR: Second index should be 1, is " << std::dec << i_v2->first << std::endl;
		pass = false;
	}

	check = connect (pattern[0], 0ULL, offset) & Vector<GF2>::Hybrid::Endianness::mask_left (len % WordTraits<Vector<GF2>::Hybrid::word_type>::bits);

	if (i_v2->second != check) {
		error << "ERROR: Second word should be " << std::hex << static_cast<uint64> (check) << ", is " << std::hex << static_cast<uint64> (i_v2->second) << std::endl;
		pass = false;
	}

	++i_v2;

	if (i_v2 != v2.end ()) {
		error << "ERROR: Did not hit end when expected." << std::endl;
		pass = false;
	}

	report << "Test 3" << std::endl;

	v.clear ();

	v.push_back (Vector<GF2>::Hybrid::value_type (0, pattern[0]));
	v.push_back (Vector<GF2>::Hybrid::value_type (2, pattern[1]));

	SparseSubvector<Vector<GF2>::Hybrid, VectorCategories::HybridZeroOneVectorTag> v3 (v, offset, WordTraits<Vector<GF2>::Hybrid::word_type>::bits + offset + len);

	SparseSubvector<Vector<GF2>::Hybrid, VectorCategories::HybridZeroOneVectorTag>::const_iterator i_v3 = v3.begin ();

	if (i_v3->first != 0) {
		error << "ERROR: First index should be 0, is " << std::dec << i_v3->first << std::endl;
		pass = false;
	}

	check = connect (pattern[0], 0ULL, offset);

	if (i_v3->second != check) {
		error << "ERROR: First word should be " << std::hex << static_cast<uint64> (check) << ", is " << std::hex << static_cast<uint64> (i_v3->second) << std::endl;
		pass = false;
	}

	++i_v3;

	if (i_v3 == v3.end ()) {
		error << "ERROR: Iterator ended prematurely." << std::endl;
		pass = false;
	}

	if (i_v3->first != 1) {
		error << "ERROR: Second index should be 1, is " << std::dec << i_v3->first << std::endl;
		pass = false;
	}

	check = connect (0ULL, pattern[1], offset);

	if (i_v3->second != check) {
		error << "ERROR: Second word should be " << std::hex << static_cast<uint64> (check) << ", is " << std::hex << static_cast<uint64> (i_v3->second) << std::endl;
		pass = false;
	}

	++i_v3;

	if (i_v3 == v3.end ()) {
		error << "ERROR: Iterator ended prematurely." << std::endl;
		pass = false;
	}

	if (i_v3->first != 2) {
		error << "ERROR: Third index should be 2, is " << std::dec << i_v3->first << std::endl;
		pass = false;
	}

	check = connect (pattern[1], 0ULL, offset) & Vector<GF2>::Hybrid::Endianness::mask_left (len % WordTraits<Vector<GF2>::Hybrid::word_type>::bits);

	if (i_v3->second != check) {
		error << "ERROR: Third word should be " << std::hex << static_cast<uint64> (check) << ", is " << std::hex << static_cast<uint64> (i_v3->second) << std::endl;
		pass = false;
	}

	++i_v3;

	if (i_v3 != v3.end ()) {
		error << "ERROR: Did not hit end when expected." << std::endl;
		pass = false;
	}

	report << "Test 4" << std::endl;

	v.clear ();

	v.push_back (Vector<GF2>::Hybrid::value_type (0, pattern[0]));

	SparseSubvector<Vector<GF2>::Hybrid, VectorCategories::HybridZeroOneVectorTag> v4 (v, offset, WordTraits<Vector<GF2>::Hybrid::word_type>::bits + offset + len);

	SparseSubvector<Vector<GF2>::Hybrid, VectorCategories::HybridZeroOneVectorTag>::const_iterator i_v4 = v4.begin ();

	if (i_v4->first != 0) {
		error << "ERROR: First index should be 0, is " << std::dec << i_v4->first << std::endl;
		pass = false;
	}

	check = connect (pattern[0], 0ULL, offset);

	if (i_v4->second != check) {
		error << "ERROR: First word should be " << std::hex << static_cast<uint64> (check) << ", is " << std::hex << static_cast<uint64> (i_v4->second) << std::endl;
		pass = false;
	}

	++i_v4;

	if (i_v4 != v4.end ()) {
		error << "ERROR: Did not hit end when expected." << std::endl;
		pass = false;
	}
	
	commentator.stop (MSG_STATUS (pass));

	return pass;
}

int main (int argc, char **argv)
{
	bool pass = true;

	static Argument args[] = {
		{ '\0' }
	};

	parseArguments (argc, argv, args);

	commentator.setBriefReportParameters (Commentator::OUTPUT_CONSOLE, false, false, false);
	commentator.getMessageClass (INTERNAL_DESCRIPTION).setMaxDepth (5);
	commentator.getMessageClass (INTERNAL_DESCRIPTION).setMaxDetailLevel (Commentator::LEVEL_UNIMPORTANT);
	commentator.getMessageClass (TIMING_MEASURE).setMaxDepth (3);

	commentator.start ("Hybrid 0-1 vector test-suite", "HybridVector");

	pass = testAdd () && pass;
	pass = testFirstNonzeroEntry () && pass;
	pass = testSparseSubvectorHybrid () && pass;

	commentator.stop (MSG_STATUS (pass));

	return pass ? 0 : -1;
}

// Local Variables:
// mode: C++
// tab-width: 8
// indent-tabs-mode: t
// c-basic-offset: 8
// End:

// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s:syntax=cpp.doxygen:foldmethod=syntax
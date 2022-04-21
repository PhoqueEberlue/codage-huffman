//
// Created by andrewmhdb on 19/04/2022.
//
#include <assert.h>
#include <malloc.h>
#include "test_occurrence.h"

void testGetCharNodeByCharacter() {
    struct char_list charList = {.last_index = 4};
    struct char_elem charElem = {.character = 0, .occurrences = 2};
    struct char_elem charElem1 = {.character = 1, .occurrences = 3};
    struct char_elem charElem2 = {.character = 2, .occurrences = 4};
    struct char_elem charElem3 = {.character = 3, .occurrences = 5};
    struct char_elem charElem4 = {.character = 4, .occurrences = 6};

    charList.char_elem_p = malloc(sizeof(struct char_elem) * 5);

    charList.char_elem_p[0] = charElem;
    charList.char_elem_p[1] = charElem1;
    charList.char_elem_p[2] = charElem2;
    charList.char_elem_p[3] = charElem3;
    charList.char_elem_p[4] = charElem4;

    struct char_elem *result = getCharNodeByCharacter(&charList, 4);

    assert(result->character == charElem4.character);
    assert(result->occurrences == charElem4.occurrences);
}

void testGenerateOccurrences() {
    struct char_elem charElem_t = {.character = 116, .occurrences = 2};
    struct char_elem charElem_h = {.character = 104, .occurrences = 2};
    struct char_elem charElem_i = {.character = 105, .occurrences = 2};
    struct char_elem charElem_s = {.character = 115, .occurrences = 2};
    struct char_elem charElem_space = {.character = 32, .occurrences = 7};
    struct char_elem charElem_a = {.character = 97, .occurrences = 4};
    struct char_elem charElem_n = {.character = 110, .occurrences = 2};
    struct char_elem charElem_e = {.character = 101, .occurrences = 4};
    struct char_elem charElem_x = {.character = 120, .occurrences = 1};
    struct char_elem charElem_m = {.character = 109, .occurrences = 2};
    struct char_elem charElem_p = {.character = 112, .occurrences = 1};
    struct char_elem charElem_l = {.character = 108, .occurrences = 1};
    struct char_elem charElem_o = {.character = 111, .occurrences = 1};
    struct char_elem charElem_f = {.character = 102, .occurrences = 3};
    struct char_elem charElem_u = {.character = 117, .occurrences = 1};
    struct char_elem charElem_r = {.character = 114, .occurrences = 1};

    struct char_list charListExpected = {.char_elem_p = &charElem_t, .last_index = 15, .size = 255};
    charListExpected.char_elem_p[0] = charElem_t;
    charListExpected.char_elem_p[1] = charElem_h;
    charListExpected.char_elem_p[2] = charElem_i;
    charListExpected.char_elem_p[3] = charElem_s;
    charListExpected.char_elem_p[4] = charElem_space;
    charListExpected.char_elem_p[5] = charElem_a;
    charListExpected.char_elem_p[6] = charElem_n;
    charListExpected.char_elem_p[7] = charElem_e;
    charListExpected.char_elem_p[8] = charElem_x;
    charListExpected.char_elem_p[9] = charElem_m;
    charListExpected.char_elem_p[10] = charElem_p;
    charListExpected.char_elem_p[11] = charElem_l;
    charListExpected.char_elem_p[12] = charElem_o;
    charListExpected.char_elem_p[13] = charElem_f;
    charListExpected.char_elem_p[14] = charElem_u;
    charListExpected.char_elem_p[15] = charElem_r;

    struct char_list *charListResult = generateOccurrences("../textes/textesimple.txt");

    for (int i = 0; i < charListExpected.last_index; ++i) {
        assert(charListExpected.char_elem_p[i].character == charListResult->char_elem_p[i].character);
        assert(charListExpected.char_elem_p[i].occurrences == charListResult->char_elem_p[i].occurrences);
    }
    assert(charListExpected.last_index == charListResult->last_index);
};

void testSortCharListByOcc() {

};

void testSortCharListByASCIICode() {

};

void testFreeCharList() {

};

void testAllOccurrences() {
    testGetCharNodeByCharacter();
    testGenerateOccurrences();
};

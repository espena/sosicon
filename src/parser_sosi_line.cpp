
/* #line 1 "parser/parser_sosi_line.rl" */
/*
 *  This file is part of the command-line tool sosicon.
 *  Copyright (C) 2012  Espen Andersen
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "parser.h"
#pragma warning ( disable: 4244 )

namespace sosicon {

    //! \cond 
    
/* #line 28 "parser_sosi_line.cpp" */
static const char _parseSosiLine_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11, 1, 12, 1, 13, 1, 14, 1, 
	15, 1, 16, 1, 17, 1, 18, 1, 
	19, 1, 20, 1, 21, 1, 22, 1, 
	23, 1, 24, 1, 25, 1, 26, 1, 
	27, 1, 28, 1, 29, 1, 30, 1, 
	31, 1, 32, 1, 33, 1, 34, 1, 
	35, 1, 36, 1, 37, 1, 38, 1, 
	39, 1, 40, 1, 41, 1, 42, 1, 
	43, 1, 44, 1, 45, 1, 46, 1, 
	47, 1, 48, 1, 49, 1, 50
};

static const short _parseSosiLine_key_offsets[] = {
	0, 0, 4, 10, 21, 28, 30, 31, 
	32, 33, 36, 41, 43, 48, 53, 54, 
	55, 56, 57, 59, 60, 61, 62, 63, 
	64, 67, 69, 70, 71, 72, 75, 77, 
	78, 79, 80, 81, 82, 83, 84, 87, 
	89, 96, 101, 107, 108, 109, 110, 111, 
	114, 116, 118, 119, 120, 121, 121, 124, 
	129, 132, 138, 143, 146, 154, 155, 156, 
	157, 157, 160, 165, 168, 174, 179, 182, 
	190, 191, 192, 193, 194, 195, 196, 196, 
	199, 204, 207, 213, 218, 221, 229, 230, 
	231, 232, 233, 234, 235, 236, 237, 238, 
	239, 242, 244, 246, 248, 249, 250, 251, 
	254, 257, 260, 266, 269, 270, 271, 274, 
	275, 276, 277, 278, 281, 283, 284, 287, 
	289, 290, 291, 292, 293, 294, 295, 296, 
	297, 300, 302, 304, 305, 306, 307, 308, 
	309, 310, 311, 312, 313, 314, 315, 316, 
	317, 318, 319, 320, 323, 328, 333, 338, 
	343, 348, 351, 356, 357, 358, 359, 362, 
	363, 366, 368, 369, 370, 371, 374, 377, 
	380, 383, 384, 385, 386, 387, 388, 389, 
	392, 394, 395, 396, 397, 398, 399, 400, 
	401, 404, 407, 410, 413, 414, 415, 416, 
	419, 421, 423, 425, 427, 428, 429, 430, 
	431, 432, 433, 434, 435, 436, 437, 438, 
	439, 440, 441, 444, 446, 451, 453, 458, 
	460, 465, 467, 472, 474, 475, 476, 477, 
	478, 479, 480, 481, 482, 485, 488, 491, 
	497, 500, 502, 503, 504, 507, 509, 511, 
	513, 515, 518, 521, 524, 527, 528, 529, 
	530, 533, 535, 536, 537, 538, 539, 540, 
	541, 542, 543, 544, 545, 546, 549, 552, 
	555, 556, 557, 558, 559, 560, 561, 562, 
	565, 568, 571, 574, 577, 583, 588, 591, 
	599, 604, 610, 611, 612, 613, 614, 617, 
	622, 622, 627, 632, 634, 634, 639, 641, 
	647, 650, 652, 654, 656, 658, 660, 662, 
	664, 670, 673, 675, 678, 679, 680, 681, 
	682, 685, 686, 687, 688, 689, 690, 691, 
	692, 693, 694, 695, 696, 697, 698, 699, 
	700, 701, 706, 712
};

static const char _parseSosiLine_trans_keys[] = {
	33, 46, 48, 57, 46, 70, 72, 75, 
	80, 84, 46, 65, 66, 71, 75, 77, 
	78, 79, 80, 83, 84, 69, 75, 76, 
	77, 79, 80, 83, 78, 84, 72, 69, 
	84, 32, 9, 13, 10, 13, 32, 9, 
	12, 10, 13, 10, 13, 32, 9, 12, 
	10, 13, 32, 9, 12, 65, 83, 74, 
	69, 78, 80, 85, 77, 77, 69, 82, 
	32, 9, 13, 48, 57, 76, 65, 78, 
	32, 9, 13, 65, 90, 79, 79, 82, 
	68, 83, 89, 83, 32, 9, 13, 48, 
	57, 10, 13, 32, 9, 12, 48, 57, 
	10, 13, 32, 9, 12, 48, 57, 65, 
	90, 97, 122, 80, 69, 78, 82, 32, 
	9, 13, 48, 57, 65, 73, 88, 45, 
	78, 32, 9, 13, 32, 9, 13, 48, 
	57, 46, 48, 57, 32, 46, 9, 13, 
	48, 57, 32, 9, 13, 48, 57, 46, 
	48, 57, 10, 13, 32, 46, 9, 12, 
	48, 57, 78, 45, 78, 32, 9, 13, 
	32, 9, 13, 48, 57, 46, 48, 57, 
	32, 46, 9, 13, 48, 57, 32, 9, 
	13, 48, 57, 46, 48, 57, 10, 13, 
	32, 46, 9, 12, 48, 57, 82, 73, 
	71, 79, 45, 78, 32, 9, 13, 32, 
	9, 13, 48, 57, 46, 48, 57, 32, 
	46, 9, 13, 48, 57, 32, 9, 13, 
	48, 57, 46, 48, 57, 10, 13, 32, 
	46, 9, 12, 48, 57, 82, 79, 68, 
	85, 75, 84, 83, 80, 69, 75, 32, 
	9, 13, 10, 13, 10, 13, 78, 83, 
	65, 86, 78, 32, 9, 13, 10, 13, 
	34, 10, 13, 34, 10, 13, 32, 34, 
	9, 12, 10, 13, 34, 82, 45, 70, 
	73, 83, 79, 82, 69, 75, 32, 9, 
	13, 10, 13, 68, 32, 9, 13, 48, 
	57, 78, 82, 69, 71, 68, 65, 84, 
	79, 32, 9, 13, 48, 57, 68, 73, 
	82, 69, 83, 83, 69, 66, 82, 85, 
	75, 83, 69, 78, 72, 69, 84, 68, 
	32, 9, 13, 32, 9, 13, 48, 57, 
	32, 9, 13, 48, 57, 32, 9, 13, 
	48, 57, 32, 9, 13, 48, 57, 32, 
	9, 13, 65, 90, 32, 9, 13, 32, 
	9, 13, 48, 57, 89, 71, 71, 78, 
	83, 84, 82, 32, 9, 13, 48, 57, 
	84, 65, 84, 32, 9, 13, 10, 13, 
	34, 10, 13, 34, 10, 13, 34, 89, 
	80, 95, 78, 66, 82, 32, 9, 13, 
	48, 57, 65, 84, 69, 78, 65, 86, 
	78, 32, 9, 13, 10, 13, 34, 10, 
	13, 34, 10, 13, 34, 79, 77, 77, 
	32, 9, 13, 48, 57, 48, 57, 48, 
	57, 48, 57, 65, 84, 82, 73, 75, 
	75, 69, 76, 78, 85, 77, 77, 69, 
	82, 32, 9, 13, 48, 57, 32, 9, 
	13, 48, 57, 48, 57, 32, 9, 13, 
	48, 57, 48, 57, 32, 9, 13, 48, 
	57, 48, 57, 32, 9, 13, 48, 57, 
	48, 57, -61, -104, 66, 74, 84, 89, 
	80, 69, 32, 9, 13, 10, 13, 34, 
	10, 13, 34, 10, 13, 32, 34, 9, 
	12, 10, 13, 34, 79, 84, 83, 84, 
	32, 9, 13, 48, 57, 48, 57, 48, 
	57, 48, 57, 32, 9, 13, 10, 13, 
	34, 10, 13, 34, 10, 13, 34, 69, 
	77, 65, 32, 9, 13, 48, 57, 79, 
	83, 73, 45, 86, 69, 82, 83, 74, 
	79, 78, 32, 9, 13, 10, 13, 34, 
	10, 13, 34, 69, 71, 78, 83, 69, 
	84, 84, 32, 9, 13, 10, 13, 34, 
	10, 13, 34, 10, 13, 34, 46, 48, 
	57, 32, 46, 9, 13, 48, 57, 32, 
	9, 13, 48, 57, 46, 48, 57, 10, 
	13, 32, 46, 9, 12, 48, 57, 10, 
	13, 32, 9, 12, 10, 13, 32, 46, 
	9, 12, 46, 46, 75, 80, 32, 9, 
	13, 32, 9, 13, 48, 57, 10, 13, 
	32, 9, 12, 10, 13, 32, 9, 12, 
	48, 57, 10, 13, 32, 9, 12, 48, 
	57, 10, 13, 32, 34, 9, 12, 10, 
	13, 34, 10, 13, 48, 57, 48, 57, 
	48, 57, 48, 57, 48, 57, 48, 57, 
	10, 13, 32, 34, 9, 12, 10, 13, 
	34, 48, 57, 10, 13, 34, 76, 65, 
	84, 69, 32, 9, 13, 58, 79, 68, 
	69, 85, 82, 86, 69, 85, 78, 75, 
	84, 69, 75, 83, 84, 10, 13, 32, 
	9, 12, 10, 13, 32, 46, 9, 12, 
	48, 57, 0
};

static const char _parseSosiLine_single_lengths[] = {
	0, 2, 6, 11, 7, 2, 1, 1, 
	1, 1, 3, 2, 3, 3, 1, 1, 
	1, 1, 2, 1, 1, 1, 1, 1, 
	1, 0, 1, 1, 1, 1, 0, 1, 
	1, 1, 1, 1, 1, 1, 1, 0, 
	3, 3, 0, 1, 1, 1, 1, 1, 
	0, 2, 1, 1, 1, 0, 1, 1, 
	1, 2, 1, 1, 4, 1, 1, 1, 
	0, 1, 1, 1, 2, 1, 1, 4, 
	1, 1, 1, 1, 1, 1, 0, 1, 
	1, 1, 2, 1, 1, 4, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 2, 2, 2, 1, 1, 1, 1, 
	3, 3, 4, 3, 1, 1, 3, 1, 
	1, 1, 1, 1, 2, 1, 1, 0, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 0, 2, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 3, 1, 
	1, 0, 1, 1, 1, 1, 3, 3, 
	3, 1, 1, 1, 1, 1, 1, 1, 
	0, 1, 1, 1, 1, 1, 1, 1, 
	1, 3, 3, 3, 1, 1, 1, 1, 
	0, 0, 0, 0, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 3, 3, 4, 
	3, 2, 1, 1, 1, 0, 0, 0, 
	0, 1, 3, 3, 3, 1, 1, 1, 
	1, 0, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 3, 3, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	3, 3, 3, 1, 2, 1, 1, 4, 
	3, 4, 1, 1, 1, 1, 1, 1, 
	0, 3, 3, 0, 0, 3, 0, 4, 
	3, 2, 0, 0, 0, 0, 0, 0, 
	4, 3, 0, 3, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 3, 4, 0
};

static const char _parseSosiLine_range_lengths[] = {
	0, 1, 0, 0, 0, 0, 0, 0, 
	0, 1, 1, 0, 1, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 1, 0, 0, 0, 1, 1, 0, 
	0, 0, 0, 0, 0, 0, 1, 1, 
	2, 1, 3, 0, 0, 0, 0, 1, 
	1, 0, 0, 0, 0, 0, 1, 2, 
	1, 2, 2, 1, 2, 0, 0, 0, 
	0, 1, 2, 1, 2, 2, 1, 2, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	2, 1, 2, 2, 1, 2, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 0, 0, 0, 0, 0, 0, 1, 
	0, 0, 1, 0, 0, 0, 0, 0, 
	0, 0, 0, 1, 0, 0, 1, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 1, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 1, 2, 2, 2, 2, 
	2, 1, 2, 0, 0, 0, 0, 0, 
	1, 1, 0, 0, 0, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	1, 0, 0, 0, 0, 0, 0, 1, 
	1, 1, 1, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 2, 1, 2, 1, 
	2, 1, 2, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 1, 0, 0, 1, 
	0, 0, 0, 0, 1, 1, 1, 1, 
	1, 1, 0, 0, 0, 0, 0, 0, 
	1, 1, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	0, 0, 0, 1, 2, 2, 1, 2, 
	1, 1, 0, 0, 0, 0, 1, 2, 
	0, 1, 1, 1, 0, 1, 1, 1, 
	0, 0, 1, 1, 1, 1, 1, 1, 
	1, 0, 1, 0, 0, 0, 0, 0, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 1, 1
};

static const short _parseSosiLine_index_offsets[] = {
	0, 0, 4, 11, 23, 31, 34, 36, 
	38, 40, 43, 48, 51, 56, 61, 63, 
	65, 67, 69, 72, 74, 76, 78, 80, 
	82, 85, 87, 89, 91, 93, 96, 98, 
	100, 102, 104, 106, 108, 110, 112, 115, 
	117, 123, 128, 132, 134, 136, 138, 140, 
	143, 145, 148, 150, 152, 154, 155, 158, 
	162, 165, 170, 174, 177, 184, 186, 188, 
	190, 191, 194, 198, 201, 206, 210, 213, 
	220, 222, 224, 226, 228, 230, 232, 233, 
	236, 240, 243, 248, 252, 255, 262, 264, 
	266, 268, 270, 272, 274, 276, 278, 280, 
	282, 285, 288, 291, 294, 296, 298, 300, 
	303, 307, 311, 317, 321, 323, 325, 329, 
	331, 333, 335, 337, 340, 343, 345, 348, 
	350, 352, 354, 356, 358, 360, 362, 364, 
	366, 369, 371, 374, 376, 378, 380, 382, 
	384, 386, 388, 390, 392, 394, 396, 398, 
	400, 402, 404, 406, 409, 413, 417, 421, 
	425, 429, 432, 436, 438, 440, 442, 446, 
	448, 451, 453, 455, 457, 459, 462, 466, 
	470, 474, 476, 478, 480, 482, 484, 486, 
	489, 491, 493, 495, 497, 499, 501, 503, 
	505, 508, 512, 516, 520, 522, 524, 526, 
	529, 531, 533, 535, 537, 539, 541, 543, 
	545, 547, 549, 551, 553, 555, 557, 559, 
	561, 563, 565, 568, 570, 574, 576, 580, 
	582, 586, 588, 592, 594, 596, 598, 600, 
	602, 604, 606, 608, 610, 613, 617, 621, 
	627, 631, 634, 636, 638, 641, 643, 645, 
	647, 649, 652, 656, 660, 664, 666, 668, 
	670, 673, 675, 677, 679, 681, 683, 685, 
	687, 689, 691, 693, 695, 697, 700, 704, 
	708, 710, 712, 714, 716, 718, 720, 722, 
	725, 729, 733, 737, 740, 745, 749, 752, 
	759, 764, 770, 772, 774, 776, 778, 781, 
	785, 786, 791, 796, 798, 799, 804, 806, 
	812, 816, 819, 821, 823, 825, 827, 829, 
	831, 837, 841, 843, 847, 849, 851, 853, 
	855, 858, 860, 862, 864, 866, 868, 870, 
	872, 874, 876, 878, 880, 882, 884, 886, 
	888, 890, 895, 901
};

static const short _parseSosiLine_trans_targs[] = {
	288, 2, 275, 0, 3, 308, 314, 317, 
	321, 325, 288, 4, 130, 155, 177, 188, 
	196, 220, 222, 233, 250, 264, 0, 5, 
	31, 42, 49, 72, 86, 99, 0, 6, 
	14, 0, 7, 0, 8, 0, 9, 0, 
	10, 10, 0, 10, 10, 13, 13, 11, 
	289, 289, 11, 289, 289, 12, 12, 0, 
	290, 290, 13, 13, 11, 15, 0, 16, 
	0, 17, 0, 18, 0, 19, 26, 0, 
	20, 0, 21, 0, 22, 0, 23, 0, 
	24, 0, 25, 25, 0, 291, 0, 27, 
	0, 28, 0, 29, 0, 30, 30, 0, 
	292, 0, 32, 0, 33, 0, 34, 0, 
	35, 0, 36, 0, 37, 0, 38, 0, 
	39, 39, 0, 40, 0, 293, 293, 41, 
	41, 40, 0, 293, 293, 41, 41, 0, 
	43, 43, 43, 0, 44, 0, 45, 0, 
	46, 0, 47, 0, 48, 48, 0, 294, 
	0, 50, 61, 0, 51, 0, 52, 0, 
	53, 0, 54, 55, 55, 0, 55, 55, 
	56, 0, 57, 57, 0, 58, 57, 58, 
	57, 0, 58, 58, 59, 0, 60, 60, 
	0, 289, 289, 12, 60, 12, 60, 0, 
	62, 0, 63, 0, 64, 0, 65, 66, 
	66, 0, 66, 66, 67, 0, 68, 68, 
	0, 69, 68, 69, 68, 0, 69, 69, 
	70, 0, 71, 71, 0, 289, 289, 12, 
	71, 12, 71, 0, 73, 0, 74, 0, 
	75, 0, 76, 0, 77, 0, 78, 0, 
	79, 80, 80, 0, 80, 80, 81, 0, 
	82, 82, 0, 83, 82, 83, 82, 0, 
	83, 83, 84, 0, 85, 85, 0, 289, 
	289, 12, 85, 12, 85, 0, 87, 0, 
	88, 0, 89, 0, 90, 0, 91, 0, 
	92, 0, 93, 0, 94, 0, 95, 0, 
	96, 0, 97, 97, 0, 0, 0, 98, 
	289, 289, 98, 100, 108, 0, 101, 0, 
	102, 0, 103, 0, 104, 104, 0, 0, 
	0, 107, 105, 295, 295, 296, 105, 295, 
	295, 106, 296, 106, 0, 0, 0, 0, 
	105, 109, 0, 110, 0, 111, 117, 120, 
	0, 112, 0, 113, 0, 114, 0, 115, 
	0, 116, 116, 0, 0, 0, 297, 118, 
	0, 119, 119, 0, 298, 0, 121, 0, 
	122, 0, 123, 0, 124, 0, 125, 0, 
	126, 0, 127, 0, 128, 0, 129, 129, 
	0, 299, 0, 131, 146, 0, 132, 0, 
	133, 0, 134, 0, 135, 0, 136, 0, 
	137, 0, 138, 0, 139, 0, 140, 0, 
	141, 0, 142, 0, 143, 0, 144, 0, 
	145, 0, 292, 0, 147, 0, 148, 148, 
	0, 148, 148, 149, 0, 150, 150, 149, 
	0, 150, 150, 151, 0, 152, 152, 151, 
	0, 152, 152, 153, 0, 154, 154, 0, 
	154, 154, 300, 0, 156, 0, 157, 0, 
	158, 0, 159, 162, 169, 0, 160, 0, 
	161, 161, 0, 301, 0, 163, 0, 164, 
	0, 165, 0, 166, 166, 0, 0, 0, 
	168, 167, 295, 295, 296, 167, 0, 0, 
	0, 167, 170, 0, 171, 0, 172, 0, 
	173, 0, 174, 0, 175, 0, 176, 176, 
	0, 302, 0, 178, 0, 179, 0, 180, 
	0, 181, 0, 182, 0, 183, 0, 184, 
	0, 185, 185, 0, 0, 0, 187, 186, 
	295, 295, 296, 186, 0, 0, 0, 186, 
	189, 0, 190, 0, 191, 0, 192, 192, 
	0, 193, 0, 194, 0, 195, 0, 292, 
	0, 197, 0, 198, 0, 199, 0, 200, 
	0, 201, 0, 202, 0, 203, 0, 204, 
	0, 205, 0, 206, 0, 207, 0, 208, 
	0, 209, 0, 210, 0, 211, 211, 0, 
	212, 0, 213, 213, 212, 0, 214, 0, 
	215, 215, 214, 0, 216, 0, 217, 217, 
	216, 0, 218, 0, 219, 219, 218, 0, 
	303, 0, 221, 0, 12, 0, 223, 0, 
	224, 0, 225, 0, 226, 0, 227, 0, 
	228, 0, 229, 229, 0, 0, 0, 232, 
	230, 304, 304, 305, 230, 304, 304, 231, 
	305, 231, 0, 0, 0, 0, 230, 234, 
	245, 0, 235, 0, 236, 0, 237, 237, 
	0, 238, 0, 239, 0, 240, 0, 241, 
	0, 242, 242, 0, 0, 0, 244, 243, 
	295, 295, 296, 243, 0, 0, 0, 243, 
	246, 0, 247, 0, 248, 0, 249, 249, 
	0, 306, 0, 251, 0, 252, 0, 253, 
	0, 254, 0, 255, 0, 256, 0, 257, 
	0, 258, 0, 259, 0, 260, 0, 261, 
	0, 262, 262, 0, 0, 0, 263, 307, 
	0, 0, 0, 307, 265, 0, 266, 0, 
	267, 0, 268, 0, 269, 0, 270, 0, 
	271, 0, 272, 272, 0, 0, 0, 274, 
	273, 295, 295, 296, 273, 0, 0, 0, 
	273, 276, 276, 0, 277, 276, 277, 276, 
	0, 277, 277, 278, 0, 279, 279, 0, 
	329, 329, 280, 279, 280, 279, 0, 329, 
	329, 280, 280, 0, 330, 330, 281, 282, 
	281, 0, 283, 0, 284, 0, 285, 0, 
	286, 0, 287, 287, 0, 287, 287, 331, 
	0, 288, 289, 289, 12, 12, 0, 290, 
	290, 13, 13, 11, 291, 0, 0, 293, 
	293, 41, 41, 0, 294, 0, 295, 295, 
	106, 296, 106, 0, 296, 296, 296, 0, 
	0, 0, 297, 298, 0, 299, 0, 300, 
	0, 301, 0, 302, 0, 303, 0, 304, 
	304, 231, 305, 231, 0, 305, 305, 305, 
	0, 306, 0, 0, 0, 0, 307, 309, 
	288, 310, 288, 311, 288, 312, 288, 313, 
	313, 288, 288, 313, 315, 288, 316, 288, 
	288, 288, 318, 288, 319, 288, 320, 288, 
	312, 288, 322, 288, 323, 288, 324, 288, 
	312, 288, 326, 288, 327, 288, 328, 288, 
	288, 288, 330, 330, 281, 281, 0, 330, 
	330, 281, 282, 281, 0, 331, 0, 0
};

static const char _parseSosiLine_trans_actions[] = {
	0, 67, 43, 0, 67, 101, 101, 101, 
	101, 101, 101, 0, 0, 0, 0, 0, 
	0, 67, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 99, 99, 99, 
	0, 0, 99, 0, 0, 0, 0, 0, 
	0, 0, 99, 99, 99, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 13, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	11, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 49, 0, 5, 5, 0, 
	0, 49, 0, 5, 5, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 9, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	57, 0, 57, 57, 0, 0, 57, 0, 
	57, 0, 0, 0, 59, 0, 59, 59, 
	0, 0, 0, 0, 59, 0, 59, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 61, 0, 61, 61, 
	0, 0, 61, 0, 61, 0, 0, 0, 
	63, 0, 63, 63, 0, 0, 0, 0, 
	63, 0, 63, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 71, 0, 
	71, 71, 0, 0, 71, 0, 71, 0, 
	0, 0, 73, 0, 73, 73, 0, 0, 
	0, 0, 73, 0, 73, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 81, 
	0, 0, 81, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 89, 0, 0, 0, 89, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	89, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 91, 0, 
	0, 0, 0, 0, 87, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 93, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 7, 0, 0, 0, 0, 0, 
	0, 0, 0, 19, 0, 0, 0, 19, 
	0, 0, 0, 17, 0, 0, 0, 17, 
	0, 0, 0, 15, 0, 0, 0, 0, 
	0, 0, 21, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 25, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 27, 0, 0, 0, 27, 0, 0, 
	0, 27, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 29, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 95, 
	0, 0, 0, 95, 0, 0, 0, 95, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 65, 0, 65, 0, 65, 0, 65, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	35, 0, 0, 0, 35, 0, 31, 0, 
	0, 0, 31, 0, 37, 0, 0, 0, 
	37, 0, 33, 0, 0, 0, 33, 0, 
	39, 0, 67, 0, 67, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	69, 1, 1, 1, 69, 1, 1, 0, 
	1, 0, 0, 0, 0, 0, 69, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 79, 0, 79, 0, 79, 0, 79, 
	0, 0, 0, 0, 0, 0, 0, 77, 
	0, 0, 0, 77, 0, 0, 0, 77, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 83, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 85, 
	0, 0, 0, 85, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	41, 0, 0, 0, 41, 0, 0, 0, 
	41, 43, 43, 0, 0, 43, 0, 43, 
	0, 0, 0, 45, 0, 45, 45, 0, 
	3, 3, 0, 45, 0, 45, 0, 3, 
	3, 0, 0, 0, 3, 3, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 47, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 99, 99, 99, 13, 0, 0, 5, 
	5, 0, 0, 0, 9, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 91, 87, 0, 93, 0, 21, 
	0, 25, 0, 29, 0, 39, 0, 1, 
	1, 0, 1, 0, 0, 1, 1, 1, 
	0, 83, 0, 0, 0, 0, 85, 0, 
	0, 0, 0, 0, 0, 23, 0, 0, 
	0, 0, 0, 55, 0, 0, 0, 0, 
	53, 0, 0, 0, 0, 0, 0, 0, 
	51, 0, 0, 0, 0, 0, 0, 0, 
	75, 0, 0, 0, 0, 0, 0, 0, 
	97, 0, 3, 3, 0, 0, 0, 3, 
	3, 0, 0, 0, 0, 47, 0, 0
};

static const int parseSosiLine_start = 1;
static const int parseSosiLine_first_final = 288;
static const int parseSosiLine_error = 0;

static const int parseSosiLine_en_main = 1;


/* #line 27 "parser/parser_sosi_line.rl" */

    //! \endcond

}

void sosicon::Parser::
parseSosiLine( std::string sosiLine )
{
    int cs = 0;
    const char* s = sosiLine.c_str();
    const char* p = s;
    const char* pe = p + sosiLine.size();
    const char* eof = pe;

    
/* #line 573 "parser_sosi_line.cpp" */
	{
	cs = parseSosiLine_start;
	}

/* #line 578 "parser_sosi_line.cpp" */
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _parseSosiLine_trans_keys + _parseSosiLine_key_offsets[cs];
	_trans = _parseSosiLine_index_offsets[cs];

	_klen = _parseSosiLine_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _parseSosiLine_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += ((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	cs = _parseSosiLine_trans_targs[_trans];

	if ( _parseSosiLine_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _parseSosiLine_actions + _parseSosiLine_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 43 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement && 
                std::find( mObjTypeFilter.begin(),
                           mObjTypeFilter.end(),
                           mCurrentElement->getData( "objtype" ) ) != mObjTypeFilter.end() ) {
                mSosiElementsSelection.push_back( mCurrentElement );
            }           
        }
	break;
	case 1:
/* #line 52 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement && mHeadElement && !mHeadElement->getData( "enhet" ).empty() ) {
                float flUnit = 0.0, flNorth = 0.0, flEast = 0.0;
                std::stringstream ssUnit, ssNorth, ssEast;
                ssUnit  << mHeadElement->getData( "enhet" );
                ssNorth << mCurrentElement->getData( "koord_n" );
                ssEast  << mCurrentElement->getData( "koord_o" );
                if( ssUnit.good() && ssNorth.good() && ssEast.good() ) {
                    ssUnit   >> flUnit;
                    ssNorth  >> flNorth;
                    ssEast   >> flEast;
                    flNorth  *= flUnit;
                    flEast   *= flUnit;
                    std::stringstream ssNorth2, ssEast2;
                    ssNorth2.unsetf( std::stringstream::scientific );
                    ssNorth2.setf( std::stringstream::fixed );
                    ssNorth2.precision( 2 );
                    ssEast2.unsetf( std::stringstream::scientific );
                    ssEast2.setf( std::stringstream::fixed );
                    ssEast2.precision( 2 );
                    ssNorth2 << flNorth;
                    ssEast2  << flEast;
                    mCurrentElement->set( "koord_n", ssNorth2.str() );
                    mCurrentElement->set( "koord_o", ssEast2.str() );
                }
            }
        }
	break;
	case 2:
/* #line 80 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                ::sosicon::sosi::CoordSys c( mCurrentElement->getData( "koordsys" ) );
                mCurrentElement->set( "koordsys_srid",        c.getSrid()        );
                mCurrentElement->set( "koordsys_beskrivelse", c.getDescription() );
                mCurrentElement->set( "koordsys_datum",       c.getDatum()       );
                mCurrentElement->set( "koordsys_projeksjon",  c.getProjection()  );
                mCurrentElement->set( "koordsys_sone",        c.getZone()        );                
            }
        }
	break;
	case 3:
/* #line 91 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "adressebruksenhet", ' ' );
            }
        }
	break;
	case 4:
/* #line 97 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "adressebruksenhet_lopenummer", (*p) );
            }
        }
	break;
	case 5:
/* #line 103 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "adressebruksenhet_etasjeplan", (*p) );
            }
        }
	break;
	case 6:
/* #line 109 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "adressebruksenhet_etasjenummer", (*p) );
            }
        }
	break;
	case 7:
/* #line 121 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "aid_bokstav", (*p) );
            }
        }
	break;
	case 8:
/* #line 127 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "aid_husnr", (*p) );
            }
        }
	break;
	case 9:
/* #line 133 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "aid_gate", (*p) );
            }
        }
	break;
	case 10:
/* #line 139 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "aid_unr", (*p) );
            }
        }
	break;
	case 11:
/* #line 145 "parser/parser_sosi_line.rl" */
	{
            mCurrentElement = new sosicon::sosi::SosiElementArea();
            mSosiElements.push_back( mCurrentElement );
        }
	break;
	case 12:
/* #line 150 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "byggnr", (*p) );
            }
        }
	break;
	case 13:
/* #line 156 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "byggstat", (*p) );
            }
        }
	break;
	case 14:
/* #line 162 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "byggtyp_nbr", (*p) );
            }
        }
	break;
	case 15:
/* #line 168 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "matrikkelnummer_gardsnr", (*p) );
            }
        }
	break;
	case 16:
/* #line 174 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "matrikkelnummer_festenr", (*p) );
            }
        }
	break;
	case 17:
/* #line 180 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "matrikkelnummer_kommunenr", (*p) );
            }
        }
	break;
	case 18:
/* #line 186 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "matrikkelnummer_bruksnr", (*p) );
            }
        }
	break;
	case 19:
/* #line 192 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "matrikkelnummer_seksjonsnr", (*p) );
            }
        }
	break;
	case 20:
/* #line 198 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "tegnsett", (*p) );
            }
        }
	break;
	case 21:
/* #line 204 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "koord_n", (*p) );
            }
        }
	break;
	case 22:
/* #line 210 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "koord_o", (*p) );
            }
        }
	break;
	case 23:
/* #line 216 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "koord_presisjon", (*p) );
            }
        }
	break;
	case 24:
/* #line 222 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "koordsys", (*p) );
            }
        }
	break;
	case 25:
/* #line 228 "parser/parser_sosi_line.rl" */
	{
            mCurrentElement = new sosicon::sosi::SosiElementCurve();
            mSosiElements.push_back( mCurrentElement );
        }
	break;
	case 26:
/* #line 233 "parser/parser_sosi_line.rl" */
	{
            mCurrentElement = new ::sosicon::sosi::SosiElementHead();
            mHeadElement = mCurrentElement;
        }
	break;
	case 27:
/* #line 238 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "id", (*p) );
            }
        }
	break;
	case 28:
/* #line 244 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "max_n", (*p) );
            }
        }
	break;
	case 29:
/* #line 250 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "max_o", (*p) );
            }
        }
	break;
	case 30:
/* #line 256 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "min_n", (*p) );
            }
        }
	break;
	case 31:
/* #line 262 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "min_o", (*p) );
            }
        }
	break;
	case 32:
/* #line 268 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "komm", (*p) );
            }
        }
	break;
	case 33:
/* #line 274 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "n_oe", (*p) );
            }
        }
	break;
	case 34:
/* #line 280 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "objtype", (*p) );
            }
        }
	break;
	case 35:
/* #line 286 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "origo_n", (*p) );
            }
        }
	break;
	case 36:
/* #line 292 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "origo_o", (*p) );
            }
        }
	break;
	case 37:
/* #line 298 "parser/parser_sosi_line.rl" */
	{
            mCurrentElement = new sosicon::sosi::SosiElementPoint();
            mSosiElements.push_back( mCurrentElement );
        }
	break;
	case 38:
/* #line 303 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "post_sted", (*p) );
            }
        }
	break;
	case 39:
/* #line 309 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "post_nr", (*p) );
            }
        }
	break;
	case 40:
/* #line 315 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "produktspek", (*p) );
            }
        }
	break;
	case 41:
/* #line 321 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "ptema", (*p) );
            }
        }
	break;
	case 42:
/* #line 327 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "sosi_versjon", (*p) );
            }
        }
	break;
	case 43:
/* #line 333 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "ssr_id", (*p) );
            }
        }
	break;
	case 44:
/* #line 339 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "ssr_snavn", (*p) );
            }
        }
	break;
	case 45:
/* #line 345 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "ssr_snforek", (*p) );
            }
        }
	break;
	case 46:
/* #line 351 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "ssr_snregdato", (*p) );
            }
        }
	break;
	case 47:
/* #line 357 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "gatenavn", (*p) );
            }
        }
	break;
	case 48:
/* #line 363 "parser/parser_sosi_line.rl" */
	{
            mCurrentElement = new sosicon::sosi::SosiElementText();
            mSosiElements.push_back( mCurrentElement );
        }
	break;
	case 49:
/* #line 368 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->append( "enhet", (*p) );
            }
        }
	break;
	case 50:
/* #line 374 "parser/parser_sosi_line.rl" */
	{
            mCurrentElement = 0;
        }
	break;
/* #line 1082 "parser_sosi_line.cpp" */
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

/* #line 507 "parser/parser_sosi_line.rl" */


};
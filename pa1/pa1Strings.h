/*
 * Filename: pa1Strings.h
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: 1/17/2019
 * Sources of Help: None.
 */

#ifndef PA1_STRINGS_H
#define PA1_STRINGS_H


#define RADIOACTIVE_PINWHEEL_USAGE \
    "Usage: %s size [upward_triangle_char [downward_triangle_char]]\n" \
    "  size: equal to the number of rows in the Radioactive Pinwheel\n" \
    "    -- must be an even integer in the bounds [%d, %d]\n" \
    "  upward_triangle_char: used for drawing the upward triangles\n" \
    "    -- must be a single character within the ASCII bounds [%d, %d]\n" \
    "    -- must be different than downward triangle char\n" \
    "    -- enter nothing to use default character (%c)\n" \
    "  downward_triangle_char: used for drawing the downward triangles\n" \
    "    -- must be a single character within the ASCII bounds [%d, %d]\n" \
    "    -- must be different than upward triangle char\n" \
    "    -- enter nothing to use default character (%c)\n"

// Error strings for the Radioactive Pinwheel size.
#define SIZE_INT_ERR \
    "\nError: Radioactive Pinwheel size must be a valid integer\n\n"
#define SIZE_CONVERTING_ERR \
    "Error: Radioactive Pinwheel size \"%s\" in base %d"
#define SIZE_BOUNDS_ERR \
    "\nError: Radioactive Pinwheel size must be within the bounds [%d, %d]\n\n"
#define SIZE_EVEN_ERR \
    "\nError: Radioactive Pinwheel size must be an even integer\n\n"

// Error strings for the triangle characters.
#define SINGLE_CHAR_ERR \
    "\nError: The %s triangle char must be a single character\n\n"
#define CHAR_BOUNDS_ERR \
    "\nError: The %s triangle char must be within ASCII bounds [%d, %d]\n\n"
#define UPWARD_DOWNWARD_SAME_CHAR_ERR \
    "\nError: Upward and downward triangle chars cannot be the same char\n\n"

// Strings to specify the names of the triangle characters.
// These are used to fill in the %s format specifiers in the strings above.
#define UPWARD_CHAR_NAME "upward"
#define DOWNWARD_CHAR_NAME "downward"


#endif /* PA1_STRINGS_H */

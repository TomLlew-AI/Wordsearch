// Libraries

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <array>
#include "funcs.hpp" // This is where all the functions are

// Variable initialisation

char possible_chars[26];

// Set the available directions

enum Directions{
    right = 0,
    down = 1,
    right_down = 2,
    right_up = 3,
    left = 4,
    up = 5,
    left_up = 6,
    left_down = 7

};

int directions = 8;

// Our program starts in the main function

int main(int argc, char *argv[]) {

    // Set up the arguments needed to generate the wordsearch defined by the user

    int width; // Width of the wordsearch
    int height; // Height of the wordsearch

    // Ensure that enough arguments must be entered
    if (argc < 4) {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    try {
        width = std::stoi(argv[1]);
        height = std::stoi(argv[2]);
        if (width <= 0 || height <= 0) {
            std::cout << "Width and height must be positive integers" << std::endl;
            return 1;
        }
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument: " << argv[1] << " or " << argv[2] << std::endl;
        return 1;
    }

    // Add the words entered by the user
    std::vector<std::string>words;

    for (int i = 3; i < argc; i++) {
        words.push_back(argv[i]);
    }

    // Convert the words to uppercase
    for (std::string &word : words) {
        word = get_upper(word);
    }

    std::vector<std::vector<char>>displayed_chars(height, std::vector<char>(width));

    // Implementing the letters from the English alphabet into possible_chars array

    for (int i = 0; i < 26; i++) {
        possible_chars[i] = (char)i + 65;
    }

    // Set up the available spaces

     // A matrix of all the spaces
    std::vector<std::vector<std::array<int, 2>>> available_spaces(
        height,
        std::vector<std::array<int, 2>>(width)
    );

    // A boolean matrix deciding whether that space is available
    std::vector<std::vector<bool>>bool_available_spaces(height, std::vector<bool>(width));

    // Implement the spaces
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            available_spaces[row][col][0] = row;
            available_spaces[row][col][1] = col;
            bool_available_spaces[row][col] = true;
        }
    }

    // Store the directions in a vector
    std::vector<int>directions_left = {right, down, right_down, right_up, left, up, left_up, left_down};

    // Loop through the words
    for (int word_index = 0; word_index < words.size(); word_index++) {

        int word_length = words[word_index].length(); // Length of the word
        int direction = directions_left[random_num(0, directions_left.size() - 1)]; // Selected direction

        // Other variables that are used to help with the process
        bool insert;
        std::vector<std::array<int, 2>>temp;
        temp.clear();

        // If the word direction is right
        if (direction == right) {

            for (int row = 0; row < height; row++) {
                for (int col = 0; col <= width - word_length; col++) {
                    insert = true;
                    for (int check_block_x = col; check_block_x < col + word_length; check_block_x++) {

                        if (!bool_available_spaces[row][check_block_x]) {
                            if (displayed_chars[row][check_block_x] == words[word_index][check_block_x - col]) {
                                insert = true;
                            } else {
                                insert = false;
                                break;
                            }
                        }
                    }

                    /* Adds the space to the current available spaces if the space is available based on the
                    condition above*/

                    if (insert) {
                        temp.push_back(available_spaces[row][col]);
                    }
                }
            }

        // The same for the other directions

        } else if (direction == down){
            for (int col = 0; col < width; col++) {
                for (int row = 0; row <= height - word_length; row++) {
                    insert = true;
                    for (int check_block_y = row; check_block_y < row + word_length; check_block_y++) {

                        if (check_block_y >= height) {
                            insert = false;
                            break;
                        }

                        if (!bool_available_spaces[check_block_y][col]) {
                            if (displayed_chars[check_block_y][col] == words[word_index][check_block_y - row]) {
                                insert = true;
                            } else {
                                insert = false;
                                break;
                            }
                        }
                    }

                    if (insert) {
                        temp.push_back(available_spaces[row][col]);
                    }
                }
            }

        } else if (direction == right_down) {
            for (int row = 0; row <= height - word_length; row++) {
                for (int col = 0; col <= width - word_length; col++) {
                    insert = true;
                    int check_block_x = col;
                    for (int check_block_y = row; check_block_y < row + word_length; check_block_y++) {

                        if (check_block_y >= height || check_block_x >= width) {
                            insert = false;
                            break;
                        }

                        if (!bool_available_spaces[check_block_y][check_block_x]) {
                            if (displayed_chars[check_block_y][check_block_x] == words[word_index][check_block_y - row]) {
                                insert = true;
                            } else {
                                insert = false;
                                break;
                            }
                        }

                        check_block_x++;
                    }

                    if (insert) {
                        temp.push_back(available_spaces[row][col]);
                    }
                }
            }
        } else if (direction == right_up) {
            for (int row = word_length - 1; row < height; row++) {
                for (int col = 0; col <= width - word_length; col++) {
                    insert = true;
                    int check_block_x = col;
                    for (int check_block_y = row; check_block_y > row - word_length; check_block_y--) {
                        if (check_block_y < 0 || check_block_x >= width) {
                            insert = false;
                            break;
                        }

                        if (!bool_available_spaces[check_block_y][check_block_x]) {
                            if (displayed_chars[check_block_y][check_block_x] == words[word_index][row - check_block_y]) {
                                insert = true;
                            } else {
                                insert = false;
                                break;
                            }
                        }

                        check_block_x++;
                    }

                    if (insert) {
                        temp.push_back(available_spaces[row][col]);
                    }
                }
            }
        } else if (direction == left) {
            for (int row = 0; row < height; row++) {
                for (int col = word_length - 1; col < width; col++) {
                    insert = true;
                    for (int check_block_x = col; check_block_x > col - word_length; check_block_x--) {

                        if (check_block_x < 0) {
                            insert = false;
                            break;
                        }


                        if (!bool_available_spaces[row][check_block_x]) {
                            if (displayed_chars[row][check_block_x] == words[word_index][col - check_block_x]) {
                                insert = true;
                            } else {
                                insert = false;
                                break;
                            }
                        }
                    }

                    if (insert) {
                        temp.push_back(available_spaces[row][col]);
                    }
                }
            }
        } else if (direction == up) {
            for (int row = word_length - 1; row < height; row++) {
                for (int col = 0; col <= width - word_length; col++) {
                    insert = true;
                    for (int check_block_y = row; check_block_y > row - word_length; check_block_y--) {
                        if (check_block_y < 0) {
                            insert = false;
                            break;
                        }

                        if (!bool_available_spaces[check_block_y][col]) {
                            if (displayed_chars[check_block_y][col] == words[word_index][row - check_block_y]) {
                                insert = true;
                            } else {
                                insert = false;
                                break;
                            }
                        }

                    }

                    if (insert) {
                        temp.push_back(available_spaces[row][col]);
                    }
                }
            }
        } else if (direction == left_up) {
            for (int row = word_length - 1; row < height; row++) {
                for (int col = word_length - 1; col < width; col++) {
                    insert = true;
                    int check_block_x = col;
                    for (int check_block_y = row; check_block_y > row - word_length; check_block_y--) {

                        if (check_block_y < 0 || check_block_x < 0) {
                            insert = false;
                            break;
                        }

                        if (!bool_available_spaces[check_block_y][check_block_x]) {
                            if (displayed_chars[check_block_y][check_block_x] == words[word_index][row - check_block_y]) {
                                insert = true;
                            } else {
                                insert = false;
                                break;
                            }
                        }

                        check_block_x--;
                    }

                    if (insert) {
                        temp.push_back(available_spaces[row][col]);
                    }
                }
            }
        } else if (direction == left_down) {
            for (int row = 0; row <= height - word_length; row++) {
                for (int col = word_index - 1; col < width; col++) {
                    insert = true;
                    int check_block_x = col;
                    for (int check_block_y = row; check_block_y < row + word_length; check_block_y++) {

                        if (check_block_y >= width || check_block_x < 0) {
                            insert = false;
                            break;
                        }

                        if (!bool_available_spaces[check_block_y][check_block_x]) {
                            if (displayed_chars[check_block_y][check_block_x] == words[word_index][check_block_y - row]) {
                                insert = true;
                            } else {
                                insert = false;
                                break;
                            }
                        }

                        check_block_x--;
                    }

                    if (insert) {
                        temp.push_back(available_spaces[row][col]);
                    }
                }
            }
        }

        // Get a random position from the temporary available spaces
        int random_index = random_num(0, temp.size() - 1);

        int random_pos[2];

        // Check if there are items. If there are, add the items to the random position
        if (temp.size() > 0) {
            random_pos[0] = temp[random_index][0];
            random_pos[1] = temp[random_index][1];

        } else {
            // Check if there are still remaining directions
            /*--REASON--
            This is used to avoid segmentation faults and still use other directions because some other ones
            could work. If there are no remaining directions, we quit the program so it doesn't crash and warn
            the user*/

            if (directions_left.size() > 1) {
                // Select another direction to try.
                for (int i = 0; i < directions_left.size(); i++) {
                    if (directions_left[i] == direction) {
                        directions_left.erase(directions_left.begin() + i);
                        break;
                    }
                }

                direction = directions_left[random_num(0, directions_left.size() - 1)];

                // We use the decrementation here to stay on the same word.
                word_index--;
                continue;

            } else {
                // Warn the user and quit the program
                std::cout << "Uh oh, something went wrong. Here are some solutions: " << std::endl;
                std::cout << "1. Rerun the program" << std::endl;
                std::cout << "2. Increase the size in blocks" << std::endl;
                return 0;
            }
        }

        // Loop through the letters in the word and add the characters to be displayed
        for (char letter : words[word_index]) {

            // Add the character to the to-be displayed characters
            displayed_chars[random_pos[0]][random_pos[1]] = letter;

            // Set the spaces the word is taking up to be false so we don't cause overlapping
            bool_available_spaces[random_pos[0]][random_pos[1]] = false;

            // These checks just check the direction
            if (direction == right) {
                random_pos[1]++;
            } else if (direction == down) {
                random_pos[0]++;
            } else if (direction == right_down) {
                random_pos[0]++;
                random_pos[1]++;
            } else if (direction == right_up) {
                random_pos[0]--;
                random_pos[1]++;
            } else if (direction == left) {
                random_pos[1]--;
            } else if (direction == up) {
                random_pos[0]--;
            } else if (direction == left_up) {
                random_pos[0]--;
                random_pos[1]--;
            } else if (direction == left_down) {
                random_pos[0]++;
                random_pos[1]--;
            }
        }

        // Reset the directions to be used on another word if everything works out successfully
        directions_left = {right, down, right_down, right_up, left, up, left_up, left_down};
    }
    // Now add the characters to the wordsearch
    bool is_taken;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            is_taken = false;
            for (char letter : possible_chars) {
                if (displayed_chars[row][col] == letter) {
                    is_taken = true;
                    break;
                }
            }
            if (is_taken) {
                continue;
            }
            displayed_chars[row][col] = possible_chars[random_num(0, 25)];
        }
    }

    // Print the wordsearch
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            std::cout << displayed_chars[row][col] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Print the words so the user can see it
    std::cout << "--WORDS--" << std::endl << std::endl;

    for (std::string word : words) {
        std::cout << word << ", ";
    }
    std::cout << std::endl;

    return 0;
}

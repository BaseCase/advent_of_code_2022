#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;


int main() {
    vector<int> trees;

    fstream input;
    input.open("./inputs/day08.input");
    string line;
    while (getline(input, line)) {
        for (char c: line) {
            if (c == '\n') continue;
            trees.push_back(c - 48);
        }
    }

    int stride = 99;
    int rows = trees.size() / stride;
    // all trees out the outer edges are visible
    int visible_count = (stride * 2) + (rows * 2) - 4;

    //
    // part 1
    //
    for (int row=1; row < rows-1; ++row) {
        for (int col=1; col < stride - 1; ++col) {
            int idx = (stride * row) + col;
            int value = trees[idx];
            bool visible;

            // above
            visible = true;
            for (int i = idx-stride; i>0; i-=stride) {
                if (trees[i] >= value) visible = false;
            }
            if (visible) {
                ++visible_count;
                continue;
            }

            // below
            visible = true;
            for (int i = idx+stride; i<trees.size(); i+=stride) {
                if (trees[i] >= value) visible = false;
            }
            if (visible) {
                ++visible_count;
                continue;
            }

            // left
            visible = true;
            for (int i = idx-1; i>=(stride*row); --i) {
                if (trees[i] >= value) visible = false;
            }
            if (visible) {
                ++visible_count;
                continue;
            }

            // right
            visible = true;
            for (int i = idx+1; i<stride*(row+1); ++i) {
                if (trees[i] >= value) visible = false;
            }
            if (visible) {
                ++visible_count;
                continue;
            }
        }
    }

    //
    // part 2
    //
    int best_scenic_score = 0;
    for (int row=1; row < rows-1; ++row) {
        for (int col=1; col < stride - 1; ++col) {
            int idx = (stride * row) + col;
            int value = trees[idx];
            int vis_left = 0;
            int vis_right = 0;
            int vis_above = 0;
            int vis_below = 0;
            int scenic_score;

            // above
            for (int i = idx-stride; i>0; i-=stride) {
                ++vis_above;
                if (trees[i] >= value)
                    break;
            }

            // below
            for (int i = idx+stride; i<trees.size(); i+=stride) {
                ++vis_below;
                if (trees[i] >= value)
                    break;
            }

            // left
            for (int i = idx-1; i>=(stride*row); --i) {
                ++vis_left;
                if (trees[i] >= value)
                    break;
            }

            // right
            for (int i = idx+1; i<stride*(row+1); ++i) {
                ++vis_right;
                if (trees[i] >= value)
                    break;
            }

            scenic_score = vis_left * vis_right * vis_above * vis_below;
            if (scenic_score > best_scenic_score)
                best_scenic_score = scenic_score;
        }
    }

    cout << "(Part 1) Number of trees visible from somewhere along the outside: " << visible_count << "\n";
    cout << "(Part 2) Best possible scenic score: " << best_scenic_score << "\n";
}

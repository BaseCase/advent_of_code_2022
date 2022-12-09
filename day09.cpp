#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <cstdlib>


using namespace std;


struct coords {
    int x;
    int y;

    bool operator<(const coords& other) const {
        return (x < other.x) || (x == other.x && y < other.y);
    }
};


struct head_move {
    char direction;
    int distance;
};


void catch_up(coords* head_pos, coords* tail_pos) {
    int x_dist = head_pos->x - tail_pos->x;
    int y_dist = head_pos->y - tail_pos->y;

    if (abs(x_dist) == 2 && abs(y_dist) == 2) {
        tail_pos->x += (x_dist / 2);
        tail_pos->y += (y_dist / 2);
    } else if (abs(x_dist) == 2) {
        tail_pos->x += (x_dist / 2);
        tail_pos->y += y_dist;
    } else if (abs(y_dist) == 2) {
        tail_pos->y += (y_dist / 2);
        tail_pos->x += x_dist;
    }
}


int main() {
    vector<head_move> moves;
    fstream input;
    input.open("./inputs/day09.input");
    string line;
    while (getline(input, line)) {
        head_move m;
        m.direction = line[0];
        m.distance = stoi(line.substr(2));
        moves.push_back(m);
    }

    // part 1
    coords head_pos = {0, 0};
    coords tail_pos = {0, 0};
    set<coords> visited_by_tail;
    visited_by_tail.insert(tail_pos);
    for (auto m: moves) {
        switch (m.direction) {
        case 'U':
            for (int i=m.distance; i>0; --i) {
                --(head_pos.y);
                catch_up(&head_pos, &tail_pos);
                visited_by_tail.insert(tail_pos);
            }
            break;

        case 'D':
            for (int i=m.distance; i>0; --i) {
                ++(head_pos.y);
                catch_up(&head_pos, &tail_pos);
                visited_by_tail.insert(tail_pos);
            }
            break;

        case 'L':
            for (int i=m.distance; i>0; --i) {
                --(head_pos.x);
                catch_up(&head_pos, &tail_pos);
                visited_by_tail.insert(tail_pos);
            }
            break;

        case 'R':
            for (int i=m.distance; i>0; --i) {
                ++(head_pos.x);
                catch_up(&head_pos, &tail_pos);
                visited_by_tail.insert(tail_pos);
            }
            break;
        }
    }

    cout << "(Part 1) Number of coords visited by tail: " << visited_by_tail.size() << ".\n";

    // part 2
    visited_by_tail.clear();
    vector<coords> rope;
    for (int i=0; i<10; ++i)
        rope.push_back({0, 0});

    for (auto m: moves) {
        switch (m.direction) {
        case 'U':
            for (int i=m.distance; i>0; --i) {
                --(rope[0].y);
                for (int r=0; r<rope.size(); ++r) {
                    coords* head = &(rope[r]);
                    coords* tail = &(rope[r+1]);
                    catch_up(head, tail);
                }
                visited_by_tail.insert(rope.back());
            }
            break;

        case 'D':
            for (int i=m.distance; i>0; --i) {
                ++(rope[0].y);
                for (int r=0; r<rope.size(); ++r) {
                    coords* head = &rope[r];
                    coords* tail = &rope[r+1];
                    catch_up(head, tail);
                }
                visited_by_tail.insert(rope.back());
            }
            break;

        case 'L':
            for (int i=m.distance; i>0; --i) {
                --(rope[0].x);
                for (int r=0; r<rope.size(); ++r) {
                    coords* head = &rope[r];
                    coords* tail = &rope[r+1];
                    catch_up(head, tail);
                }
                visited_by_tail.insert(rope.back());
            }
            break;

        case 'R':
            for (int i=m.distance; i>0; --i) {
                ++(rope[0].x);
                for (int r=0; r<rope.size(); ++r) {
                    coords* head = &rope[r];
                    coords* tail = &rope[r+1];
                    catch_up(head, tail);
                }
                visited_by_tail.insert(rope.back());
            }
            break;
        }
    }

    cout << "(Part 2) Number of coords visited by longer rope's tail: " << visited_by_tail.size() << ".\n";
}

#include <cassert>
#include <vector>
#include <string>
#include <memory>

#ifndef DUNGEON_H
#define DUNGEON_H

#endif

#pragma once

class Room;

class Door {
 public:
    bool IsOpen() const { return open_; }

    // returns true if key opened door
    bool TryOpen(const std::string& key) {
        if (key_ == key) open_ = true;
        return open_;
    }

    // door must be open
    Room* GoThrough() {
        assert(open_);
        return to_;
    }

    explicit Door(Room* to) : to_(to), open_(true) {}
    Door(Room* to, const std::string& key) : to_(to), open_(false), key_(key) {}

    Door(const Door&) = delete;
    Door(Door&&) = delete;
    Door& operator = (const Door&) = delete;
    Door& operator = (Door&&) = delete;

 private:
    bool open_;
    std::string key_;
    Room* to_;
};

class Room {
 public:
    bool IsFinal() { return is_final_; }

    size_t NumKeys() { return keys_.size(); }
    std::string GetKey(size_t key_index) { return keys_[key_index]; }

    size_t NumDoors() { return doors_.size(); }
    Door* GetDoor(size_t door_index) { return doors_[door_index].get(); }

    explicit Room(bool is_final) : is_final_(is_final) {}
    void AddDoor(Room* to) {
        doors_.emplace_back(new Door(to));
        to->doors_.emplace_back(new Door(this));
    }

    void AddDoorWithKey(Room* to, const std::string& key) {
        doors_.emplace_back(new Door(to, key));
        to->doors_.emplace_back(new Door(this, key));
    }

    void AddKey(const std::string& key) { keys_.push_back(key); }

    Room(const Room&) = delete;
    Room(Room&&) = delete;
    Room& operator = (const Room&) = delete;
    Room& operator = (Room&&) = delete;

 private:
    bool is_final_;

    std::vector<std::unique_ptr<Door>> doors_;
    std::vector<std::string> keys_;
};

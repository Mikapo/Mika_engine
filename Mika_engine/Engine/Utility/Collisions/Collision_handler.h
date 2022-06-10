#pragma once

#include "Collision.h"
#include "Datatypes/Axis.h"
#include "Datatypes/Hit_result.h"
#include <optional>
#include <unordered_map>
#include <memory>
#include <unordered_set>
#include <vector>

class Collision_component;
class Actor;
struct Line;
class Collision_handler
{
public:
    void unregister_component(Collision_component* component);
    void update_component(Collision_component* component, std::shared_ptr<Collision> collision);
    std::optional<Collision_component*> find_collisions(const Collision* collision, const Collision_component* component) const;
    std::optional<Hit_result> find_overlaps_with_line(Line* line, const std::unordered_set<Actor*>& ignored_actors);

private:
	struct Node
    {
        Node(Collision_component* component, std::shared_ptr<Collision> collision) 
            : m_component(component), m_collision(collision) {}

        Collision_component* m_component;
        std::shared_ptr<Collision> m_collision;
        Axis m_axis = Axis::x;
        Node* m_parent = nullptr;
        Node* m_left = nullptr;
        Node* m_right = nullptr;
	};

    enum class Comparison_result : uint8_t
    {
        left,
        right
    };

    std::optional<Collision_component*> find_collisions_recurssion(
        Axis axis, Node* current_node, const Collision* collision, const Collision_component* component) const;

    void  find_overlaps_with_line_recurssion(std::vector<Hit_result>& out_hits, Axis axis, Node* current_node, const Line* line) const;

    Node* construct_node(Collision_component* component, std::shared_ptr<Collision> collision);
    void destruct_node(Collision_component* component);
    void add_node_to_structure(Node* node);
    void add_node_to_structure_recurssion(Axis axis, Node* current_node, Node* node_to_add);
    void remove_node_from_structure(Node* node);
    Axis next_axis(Axis axis) const;
    Comparison_result compare_nodes(Axis axis, Node* a, Node* b) const;

    Node* m_root = nullptr;
    std::unordered_map<Collision_component*, Node*> m_nodes;

};

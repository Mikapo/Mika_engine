#include "Collision_handler.h"
#include "Utility/Collisions/Line.h"
#include "Objects/Components/Scene_components/collision_component.h"
#include <stdexcept>
#include <limits>

void Collision_handler::unregister_component(Collision_component* component)
{
    if (!m_nodes.contains(component))
        throw std::invalid_argument("does not contains in structure");

    remove_node_from_structure(m_nodes[component]);
}

void Collision_handler::update_component(Collision_component* component, std::shared_ptr<Collision> collision)
{
    if (m_nodes.contains(component))
        remove_node_from_structure(m_nodes[component]);   

    Node* node = construct_node(component, collision);
    add_node_to_structure(node);
}

std::optional<Collision_component*> Collision_handler::find_collisions(
    const Collision* collision, const Collision_component* component) const
{
    if (m_root)
        return find_collisions_recurssion(Axis::x, m_root, collision, component);
    else
        return std::optional<Collision_component*>();
}

std::optional<Hit_result> Collision_handler::find_overlaps_with_line(
    Line* line, const std::unordered_set<Actor*>& ignored_actors)
{ 
    if (m_root)
    {
        std::vector<Hit_result> hit_results;
        find_overlaps_with_line_recurssion(hit_results, Axis::x, m_root, line);

        bool found_valid_hit = false;
        size_t hit_index = 0;
        float lenght = std::numeric_limits<float>::infinity();

        for (size_t i = 0; i < hit_results.size(); ++i)
        {
            Actor* hit_actor = hit_results[i].m_component->get_owner();
            const bool is_in_ignored_list = ignored_actors.contains(hit_actor);

            if (!is_in_ignored_list && hit_results[i].m_lenght < lenght)
            {
                found_valid_hit = true;
                hit_index = i;
                lenght = hit_results[i].m_lenght;
            }
        }
           
        if (found_valid_hit && hit_index >= 0)
            return hit_results[hit_index];
    }
   
    return std::optional<Hit_result>(); 
}

std::optional<Collision_component*> Collision_handler::find_collisions_recurssion(
    Axis axis, Node* current_node, const Collision* collision, const Collision_component* component) const
{
    const auto current_collision = current_node->m_collision;

    if (component != current_node->m_component && current_collision->is_overlapping(collision))
        return current_node->m_component;

    const glm::vec3 current_box_location = collision->get_origin();

    switch (collision->compare_to_axis(current_box_location, axis))
    {
    case Axis_comparison_result::right:
        if (current_node->m_right)
            return find_collisions_recurssion(next_axis(axis), current_node->m_right, collision, component);
        break;
    case Axis_comparison_result::left:
        if (current_node->m_left)
            return find_collisions_recurssion(next_axis(axis), current_node->m_left, collision, component);
        break;
    case Axis_comparison_result::overlap:
        std::optional<Collision_component*> result;

        if (current_node->m_right)
            result = find_collisions_recurssion(next_axis(axis), current_node->m_right, collision, component);
        if (result.has_value())
            return result;

        if (current_node->m_left)
            result = find_collisions_recurssion(next_axis(axis), current_node->m_left, collision, component);
        if (result.has_value())
            return result;
        break;
    }

    return std::optional<Collision_component*>();
}

void Collision_handler::find_overlaps_with_line_recurssion(
    std::vector<Hit_result>& out_hits, Axis axis, Node* current_node, const Line* line) const
{
    const auto current_collision = current_node->m_collision;
    auto overlap = current_collision->is_overlapping_with_line(*line);

    if (overlap.has_value())
    {
        overlap.value().m_component = current_node->m_component;
        out_hits.emplace_back(overlap.value());
    }

    const glm::vec3 current_box_location = current_collision->get_origin();

    switch (line->compare_to_axis(current_box_location, axis))
    {
    case Axis_comparison_result::right:
        if (current_node->m_right)
            return find_overlaps_with_line_recurssion(out_hits, next_axis(axis), current_node->m_right, line);
        break;
    case Axis_comparison_result::left:
        if (current_node->m_left)
            return find_overlaps_with_line_recurssion(out_hits, next_axis(axis), current_node->m_left, line);
        break;
    case Axis_comparison_result::overlap:
        if (current_node->m_right)
            find_overlaps_with_line_recurssion(out_hits, next_axis(axis), current_node->m_right, line);

        if (current_node->m_left)
            find_overlaps_with_line_recurssion(out_hits, next_axis(axis), current_node->m_left, line);
        break;
    }
}

Collision_handler::Node* Collision_handler::construct_node(
    Collision_component* component, std::shared_ptr<Collision> collision)
{ 
    Node* node = new Node(component, collision);
    m_nodes.insert({component, node});
    return node;
}

void Collision_handler::destruct_node(Collision_component* component)
{ 
    if (!m_nodes.contains(component))
        throw std::invalid_argument("node does not exists");

    Node* node = m_nodes[component]; 
    delete node;
    m_nodes.erase(component);
}

void Collision_handler::add_node_to_structure(Node* node) 
{ 
    if (!m_root)
        m_root = node;
    else
        add_node_to_structure_recurssion(Axis::x, m_root, node);
}

void Collision_handler::add_node_to_structure_recurssion(Axis axis, Node* current_node, Node* node_to_add)
{
    node_to_add->m_axis = next_axis(axis);
    node_to_add->m_parent = current_node;

    switch(compare_nodes(axis, node_to_add, current_node))
    {
    case Comparison_result::right:
        if (current_node->m_right)
            return add_node_to_structure_recurssion(next_axis(axis), current_node->m_right, node_to_add);
        else
            current_node->m_right = node_to_add;
        break;
    case Comparison_result::left:
        if (current_node->m_left)
            return add_node_to_structure_recurssion(next_axis(axis), current_node->m_left, node_to_add);
        else
            current_node->m_left = node_to_add;
        break;
    }
}


void Collision_handler::remove_node_from_structure(Node* node) 
{ 
    if (!m_nodes.contains(node->m_component))
        throw std::invalid_argument("node does not exists in structure");

    Node* left = node->m_left;
    Node* right = node->m_right;
    Node* parent = node->m_parent;

    if (m_root == node)
        m_root = nullptr;
    else if (parent->m_left == node)
        parent->m_left = nullptr;
    else if (parent->m_right == node)
        parent->m_right = nullptr;
    else
        throw std::runtime_error("never should get here");

    destruct_node(node->m_component);

    if (left)
        add_node_to_structure(left);
    if (right)
        add_node_to_structure(right);
}

Axis Collision_handler::next_axis(Axis axis) const
{ 
    switch (axis)
    {
    case Axis::x:
        return Axis::y;
    case Axis::y:
        return Axis::z;
    case Axis::z:
        return Axis::x;
    default:
        throw std::invalid_argument("invalid enum");
    }
}

Collision_handler::Comparison_result Collision_handler::compare_nodes(Axis axis, Node* a, Node* b) const
{ 
    const glm::vec3 origin = a->m_collision->get_origin();
    const glm::vec3 other_origin = b->m_collision->get_origin();

    switch (axis)
    {
    case Axis::x:
        if (origin.x >= other_origin.x)
            return Comparison_result::right;
        break;
    case Axis::y:
        if (origin.y >= other_origin.y)
            return Comparison_result::right;
        break;
    case Axis::z:
        if (origin.z >= other_origin.z)
            return Comparison_result::right;
        break;
    }

    return Comparison_result::left;
}

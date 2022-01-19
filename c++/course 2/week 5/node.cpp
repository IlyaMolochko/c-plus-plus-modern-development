#include "node.h"

bool EmptyNode::Evaluate(const Date &date, const std::string &event) {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison &comparison,
                                       const Date &date) :
        comparison_(comparison),
        date_(date) {}

bool DateComparisonNode::Evaluate(const Date &date, const std::string &event) {
    switch (comparison_) {
        case Comparison::Less:
            return date < date_;
        case Comparison::LessOrEqual:
            return date <= date_;
        case Comparison::Greater:
            return date > date_;
        case Comparison::GreaterOrEqual:
            return date >= date_;
        case Comparison::Equal:
            return date == date_;
        case Comparison::NotEqual:
            return date != date_;
    }
}

EventComparisonNode::EventComparisonNode(const Comparison &comparison,
                                         const std::string &event) :
        comparison_(comparison),
        event_(event) {}

bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) {
    switch (comparison_) {
        case Comparison::Less:
            return event < event_;
        case Comparison::LessOrEqual:
            return event <= event_;
        case Comparison::Greater:
            return event > event_;
        case Comparison::GreaterOrEqual:
            return event >= event_;
        case Comparison::Equal:
            return event == event_;
        case Comparison::NotEqual:
            return event != event_;
    }
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &logical_operation,
                                           const std::shared_ptr<Node> &left_node,
                                           const std::shared_ptr<Node> &right_node) :
        logical_operation_(logical_operation),
        left_node_(left_node),
        right_node_(right_node) {}

bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) {
    switch (logical_operation_) {
        case LogicalOperation::And:
            return left_node_->Evaluate(date, event) and right_node_->Evaluate(date, event);
        case LogicalOperation::Or:
            return left_node_->Evaluate(date, event) or right_node_->Evaluate(date, event);
    }
}

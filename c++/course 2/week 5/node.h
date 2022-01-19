#pragma once
#include "date.h"

#include <string>
#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    And,
    Or
};

class Node {
public:
    virtual bool Evaluate(const Date &date,
                          const std::string &event) = 0;
};

class EmptyNode : public Node {
    bool Evaluate(const Date &date,
                  const std::string &event) override ;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison &comparison,
                       const Date &date);

    bool Evaluate(const Date &date,
                  const std::string &event) override ;

private:
    const Comparison comparison_;
    const Date date_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison &comparison,
                        const std::string &value);

    bool Evaluate(const Date &date,
                  const std::string &event) override ;


private:
    const Comparison comparison_;
    const std::string event_;
};

class LogicalOperationNode : public Node {
public:

    LogicalOperationNode(const LogicalOperation &logical_operation,
                         const std::shared_ptr<Node> &left_node,
                         const std::shared_ptr<Node> &right_node);

    bool Evaluate(const Date &date,
                  const std::string &event) override ;

private:
    const LogicalOperation logical_operation_;
    std::shared_ptr<Node> left_node_;
    std::shared_ptr<Node> right_node_;
};
#pragma once

#include "date.h"

using namespace std;

enum class Comparison{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation{
    Or,
    And
};

struct Node {
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate (const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, const Date& date);

    bool Evaluate (const Date& date, const string& event) const override;

private:
    Comparison cmp_;
    Date date_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, const string& event);

    bool Evaluate (const Date& date, const string& event) const override;

private:
    Comparison cmp_;
    const string event_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode (LogicalOperation logicalOperation, shared_ptr<const Node> left, shared_ptr<const Node> right);

    bool Evaluate (const Date& date, const string& event) const override;

private:
    LogicalOperation logicalOperation_;
    shared_ptr<const Node> left_, right_;
};
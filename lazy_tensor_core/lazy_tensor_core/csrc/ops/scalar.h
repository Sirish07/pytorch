#pragma once

#include <ATen/core/Formatting.h>
#include <c10/core/Scalar.h>
#include <torch/csrc/lazy/ts_backend/ts_node.h>

#include <iostream>

namespace torch_lazy_tensors {
namespace ir {
namespace ops {

// Differently from Constant, this is a scalar value broadcasted to a shape.
// Even though a Constant could have been used, for simple scalars broadcasted
// to big shapes, the Constant leads to big literals expanded within the
// computation graph.
class Scalar : public torch::lazy::TsNode {
 public:
  Scalar(const at::Scalar& value, torch::lazy::Shape shape);
  Scalar(const at::Scalar& value, c10::ScalarType  type);

  std::string ToString() const override;

  const at::Scalar& value() const { return value_; }

 private:
  at::Scalar value_;
};

torch::lazy::hash_t ScalarHash(const at::Scalar& s);

using at::operator<<;

inline torch::lazy::NodePtr ScalarOp(const at::Scalar& value,
                                     c10::ScalarType type) {
  return torch::lazy::MakeNode<Scalar>(value, type);
}

}  // namespace ops
}  // namespace ir
}  // namespace torch_lazy_tensors

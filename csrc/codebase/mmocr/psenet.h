// Copyright (c) OpenMMLab. All rights reserved.

#ifndef MMDEPLOY_CSRC_CODEBASE_MMOCR_PSENET_H_
#define MMDEPLOY_CSRC_CODEBASE_MMOCR_PSENET_H_

#include "codebase/mmocr/mmocr.h"
#include "core/device.h"
#include "core/registry.h"
#include "core/tensor.h"
#include "opencv2/core.hpp"

namespace mmdeploy {
namespace mmocr {

class PseHeadImpl {
 public:
  virtual ~PseHeadImpl() = default;

  virtual void Init(const Stream& stream) { stream_ = stream; }

  virtual Result<void> Process(Tensor preds,                 //
                               float min_kernel_confidence,  //
                               cv::Mat_<float>& score,       //
                               cv::Mat_<uint8_t>& masks,     //
                               cv::Mat_<int>& label,         //
                               int& region_num) = 0;

 protected:
  Stream stream_;
};

}  // namespace mmocr

MMDEPLOY_DECLARE_REGISTRY(mmocr::PseHeadImpl);

}  // namespace mmdeploy

#endif  // MMDEPLOY_CSRC_CODEBASE_MMOCR_PSENET_H_

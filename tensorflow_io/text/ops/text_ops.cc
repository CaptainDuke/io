/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/core/framework/common_shape_fns.h"
#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/shape_inference.h"
#include "re2/re2.h"

namespace tensorflow {

REGISTER_OP("RE2FullMatch")
    .Input("input: string")
    .Output("output: bool")
    .Output("groups: string")
    .Attr("pattern: string")
    .SetShapeFn([](shape_inference::InferenceContext* c) {
      if (!c->RankKnown(c->input(0))) {
        c->set_output(0, c->UnknownShape());
        c->set_output(1, c->UnknownShape());
        return Status::OK();
      }
      string pattern;
      TF_RETURN_IF_ERROR(c->GetAttr("pattern", &pattern));
      RE2 re(pattern, RE2::Quiet);
      if (!re.ok()) {
        return errors::InvalidArgument("unable to compile pattern '", pattern, "': ", re.error());
      }
      shape_inference::ShapeHandle shape;
      TF_RETURN_IF_ERROR(c->WithRankAtLeast(c->input(0), 0, &shape));
      shape_inference::ShapeHandle output_shape;
      TF_RETURN_IF_ERROR(c->Concatenate(shape, c->Vector(re.NumberOfCapturingGroups()), &output_shape));
      c->set_output(0, c->input(0));
      c->set_output(1, output_shape);
      return Status::OK();
    });

REGISTER_OP("TextStreamInput")
    .Input("source: string")
    .Output("handle: variant")
    .Attr("filters: list(string) = []")
    .Attr("columns: list(string) = []")
    .Attr("schema: string = ''")
    .SetShapeFn([](shape_inference::InferenceContext* c) {
       c->set_output(0, c->MakeShape({c->UnknownDim()}));
       return Status::OK();
     });

REGISTER_OP("TextStreamDataset")
    .Input("input: T")
    .Input("batch: int64")
    .Output("handle: variant")
    .Attr("output_types: list(type) >= 1")
    .Attr("output_shapes: list(shape) >= 1")
    .Attr("T: {string, variant} = DT_VARIANT")
    .SetIsStateful()
    .SetShapeFn([](shape_inference::InferenceContext* c) {
       c->set_output(0, c->MakeShape({}));
       return Status::OK();
     });

REGISTER_OP("TextInput")
    .Input("source: string")
    .Output("handle: variant")
    .Attr("filters: list(string) = []")
    .Attr("columns: list(string) = []")
    .Attr("schema: string = ''")
    .SetShapeFn([](shape_inference::InferenceContext* c) {
       c->set_output(0, c->MakeShape({c->UnknownDim()}));
       return Status::OK();
     });

REGISTER_OP("TextDataset")
    .Input("input: T")
    .Input("batch: int64")
    .Output("handle: variant")
    .Attr("output_types: list(type) >= 1")
    .Attr("output_shapes: list(shape) >= 1")
    .Attr("T: {string, variant} = DT_VARIANT")
    .SetIsStateful()
    .SetShapeFn([](shape_inference::InferenceContext* c) {
       c->set_output(0, c->MakeShape({}));
       return Status::OK();
     });

REGISTER_OP("TextDatasetOutput")
    .Input("dataset: variant")
    .Input("filename: string")
    .SetIsStateful()
    .SetShapeFn([](shape_inference::InferenceContext* c) {
       return Status::OK();
     });

REGISTER_OP("CsvDatasetOutput")
    .Input("dataset: variant")
    .Input("filename: string")
    .SetIsStateful()
    .SetShapeFn([](shape_inference::InferenceContext* c) {
       return Status::OK();
     });

REGISTER_OP("TextOutputSequence")
    .Input("destination: string")
    .Output("sequence: resource")
    .Attr("container: string = ''")
    .Attr("shared_name: string = ''")
    .SetIsStateful()
    .SetShapeFn(shape_inference::ScalarShape);
REGISTER_OP("TextOutputSequenceSetItem")
    .Input("sequence: resource")
    .Input("index: int64")
    .Input("item: string")
    .SetIsStateful()
    .SetShapeFn(shape_inference::ScalarShape);

}  // namespace tensorflow

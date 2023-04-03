/// Copyright (C) 2020-2023 Huawei Technologies Co., Ltd.
///
/// This file is part of Cooddy, distributed under the GNU GPL version 3 with a Linking Exception.
/// For full terms see https://github.com/program-analysis-team/cooddy/blob/master/LICENSE.txt.
#ifndef COODDY_ANALYZER_SOURCE_SOLVER_PROCESSORS_ASMINSTRUCTION_H_
#define COODDY_ANALYZER_SOURCE_SOLVER_PROCESSORS_ASMINSTRUCTION_H_

#include <ast/AsmStatement.h>

namespace Processor {

class AsmInstruction : public InstructionProcessor {
    void Compile(const Node& node, CompileContext& context) override
    {
        auto children = node.GetChildren();
        context.Add<uint16_t>(children.size());
        for (auto& child : children) {
            context.Compile(child);
        }
    }
    // LCOV_EXCL_START
    z3::expr Execute(ExecutionContext& context, SymbolId& symbolId) override
    {
        auto childCount = context.Get<uint16_t>();
        for (uint32_t i = 0; i < childCount; ++i) {
            context.Execute();
        }
        return context->CreateSymbolExpr(symbolId);
    }
    // LCOV_EXCL_STOP
};

};  // namespace Processor

#endif  // COODDY_ANALYZER_SOURCE_SOLVER_PROCESSORS_ASMINSTRUCTION_H_
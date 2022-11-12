#include "fuzzfactory.hpp"

using namespace fuzzfactory;

class BranchDepthFeedback : public DomainFeedback<BranchDepthFeedback> {
public:
    BranchDepthFeedback(Module& M) : DomainFeedback<BranchDepthFeedback>(M, "__afl_branch_dsf") { }

    void visitBranchInst (BranchInst &r) {
        // check if it is a conditional branch
        if (r.isConditional()){
            auto key = createProgramLocation(); // static random value

            // Insert call to `dsf_increment(dsf_map, key, 1)`;
            auto irb = insert_before(r); // Get a handle to the LLVM IR builder
            irb.CreateCall(DsfIncrementFunction, {DsfMapVariable, key, getConst(1)}); 
        }
    }

    void visitSwitchInst (SwitchInst &r) {
        auto key = createProgramLocation(); // static random value

        // Insert call to `dsf_increment(dsf_map, key, 1)`;
        auto irb = insert_before(r); // Get a handle to the LLVM IR builder
        irb.CreateCall(DsfIncrementFunction, {DsfMapVariable, key, getConst(1)}); 
    }

    void visitIndirectBranchInst (IndirectBrInst &r) {
        auto key = createProgramLocation(); // static random value

        // Insert call to `dsf_increment(dsf_map, key, 1)`;
        auto irb = insert_before(r); // Get a handle to the LLVM IR builder
        irb.CreateCall(DsfIncrementFunction, {DsfMapVariable, key, getConst(1)}); 
    }

    void visitCallInst (CallInst &r) {
        auto key = createProgramLocation(); // static random value

        // Insert call to `dsf_increment(dsf_map, key, 1)`;
        auto irb = insert_before(r); // Get a handle to the LLVM IR builder
        irb.CreateCall(DsfIncrementFunction, {DsfMapVariable, key, getConst(1)}); 
    }
};

FUZZFACTORY_REGISTER_DOMAIN(BranchDepthFeedback);

/**
 * Open Space Program
 * Copyright © 2019-2022 Open Space Program Project
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

#include "tasks.h"
#include "worker.h"

#include "../bitvector.h"

#include <entt/entity/storage.hpp>

#include <cassert>
#include <variant>
#include <vector>

namespace osp
{

struct ExecPipeline
{
    StageBits_t     triggered           {0};
    StageId         currentStage        {0};

    int             tasksQueuedRun      {0};
    int             tasksQueuedBlocked  {0};

    int             stageReqTaskCount   {0};
    int             taskReqStageCount   {0};
};

struct BlockedTask
{
    int             remainingTaskReqStg;
    PipelineId      pipeline;
};

/**
 * @brief The ExecContext class
 *
 * Pipelines are marked dirty (m_plDirty.set(pipeline int)) if...
 * * All of its running tasks just finished
 * * Not running but required by another pipeline
 */
struct ExecContext
{
    KeyedVec<PipelineId, ExecPipeline>  plData;
    BitVector_t                         plDirty;


    entt::basic_sparse_set<TaskId>      tasksQueuedRun;
    entt::basic_storage<BlockedTask, TaskId> tasksQueuedBlocked;

    KeyedVec<AnyStageId, int>           anystgReqByTaskCount;

    // used for enqueue_dirty as temporary values

    KeyedVec<PipelineId, StageId>       plNextStage;
    BitVector_t                         plDirtyNext;

    // 'logging'

    struct EnqueueCycleStart { };

    struct StageChange
    {
        PipelineId  pipeline;
        StageId     stageOld;
        StageId     stageNew;
    };

    struct EnqueueTask
    {
        PipelineId  pipeline;
        StageId     stage;
        TaskId      task;
        bool        blocked;
    };

    struct EnqueueTaskReq
    {
        PipelineId  pipeline;
        StageId     stage;
    };

    struct CompleteTask
    {
        TaskId      task;
    };

    struct TriggeredStage
    {
        TaskId      task;
        PipelineId  pipeline;
        StageId     stage;
    };

    struct UnblockTask
    {
        TaskId      task;
    };

    using LogMsg_t = std::variant<EnqueueCycleStart, StageChange, EnqueueTask, EnqueueTaskReq, CompleteTask, TriggeredStage, UnblockTask>;

    std::vector<LogMsg_t>           logMsg;
    bool                            doLogging{true};

    // TODO: Consider multithreading. something something work stealing...
    //  * Allow multiple threads to search for and execute tasks. Atomic access
    //    for ExecContext? Might be messy to implement.
    //  * Only allow one thread to search for tasks, assign tasks to other
    //    threads if they're available before running own task. Another thread
    //    can take over once it completes its task. May be faster as only one
    //    thread is modifying ExecContext, and easier to implement.
    //  * Plug into an existing work queue library?

}; // struct ExecContext

void exec_resize(Tasks const& tasks, TaskGraph const& graph, ExecContext &rOut);

void exec_resize(Tasks const& tasks, ExecContext &rOut);

inline void set_dirty(ExecContext &rExec, TplPipelineStage tpl) noexcept
{
    rExec.plData[tpl.pipeline].triggered |= 1 << int(tpl.stage);
    rExec.plDirty.set(std::size_t(tpl.pipeline));
}

void enqueue_dirty(Tasks const& tasks, TaskGraph const& graph, ExecContext &rExec) noexcept;

void mark_completed_task(Tasks const& tasks, TaskGraph const& graph, ExecContext &rExec, TaskId const task, TriggerOut_t dirty) noexcept;



} // namespace osp

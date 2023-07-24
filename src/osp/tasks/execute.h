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
    int             tasksQueuedRun      {0};
    int             tasksQueuedBlocked  {0};

    int             tasksReqOwnStageLeft{0};
    int             ownStageReqTasksLeft{0};

    StageId         stage               { lgrn::id_null<StageId>() };
    bool            tasksQueued         { false };
    bool            running             { false };
    bool            doLoop              { false };
    bool            cancelOptionals     { false };
};

struct BlockedTask
{
    int             reqStagesLeft;
    PipelineId      pipeline;
};

/**
 * @brief
 */
struct ExecContext
{
    KeyedVec<PipelineId, ExecPipeline>  plData;

    entt::basic_sparse_set<TaskId>              tasksQueuedRun;
    entt::basic_storage<BlockedTask, TaskId>    tasksQueuedBlocked;

    BitVector_t                         plAdvance;
    BitVector_t                         plAdvanceNext;
    bool                                hasPlAdvance  {false};

    BitVector_t                         plRequestRun;
    bool                                hasRequestRun {false};


    // 'logging'

    struct EnqueueStart { };
    struct EnqueueCycle { };
    struct EnqueueEnd { };

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

    struct UnblockTask
    {
        TaskId      task;
    };

    struct CompleteTask
    {
        TaskId      task;
    };

    struct CompleteTaskTrigger
    {
        PipelineId  pipeline;
        StageId     stage;
    };

    struct ExternalTrigger
    {
        PipelineId  pipeline;
        StageId     stage;
    };

    using LogMsg_t = std::variant<EnqueueStart, EnqueueCycle, EnqueueEnd, StageChange, EnqueueTask, EnqueueTaskReq, UnblockTask, CompleteTask, CompleteTaskTrigger, ExternalTrigger>;

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

void pipeline_run(ExecContext &rExec, PipelineId pipeline);

void pipeline_cancel_optionals(Tasks const& tasks, TaskGraph const& graph, ExecContext &rExec, PipelineId pipeline);

void pipeline_cancel_loop(Tasks const& tasks, TaskGraph const& graph, ExecContext &rExec, PipelineId pipeline);

void enqueue_dirty(Tasks const& tasks, TaskGraph const& graph, ExecContext &rExec) noexcept;

void complete_task(Tasks const& tasks, TaskGraph const& graph, ExecContext &rExec, TaskId task, TaskActions actions) noexcept;



} // namespace osp

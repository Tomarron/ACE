/**
 * @file Deployment_Completion.h
 * @author William R. Otte <wotte@dre.vanderbilt.edu>
 *
 * $Id: Deployment_Completion.h 91982 2010-09-23 20:43:54Z wotte $
 *
 * Future observer that signals when the scheduler has completed.
 */

#ifndef DEPLOYMENT_COMPLETION_H
#define DEPLOYMENT_COMPLETION_H

#include /**/ "ace/pre.h"

#include "ace/Condition_T.h"
#include "ace/Future.h"
#include "Completion/Completion_Counter_Base.h"
#include "dance/LocalityManager/Scheduler/Deployment_Event.h"
#include "dance/LocalityManager/Scheduler/Deployment_Scheduler.h"

namespace DAnCE
{
  /**
   * @class Event_Handler
   */
  class Deployment_Scheduler_Export Deployment_Completion
    : public virtual ACE_Future_Observer< Event_Result >,
      public virtual Completion_Counter_Base< TAO_SYNCH_MUTEX >
  {
  public:
    Deployment_Completion (Deployment_Scheduler &sched);

    virtual ~Deployment_Completion (void);

    virtual void update (const Event_Future &future);

    void accept (Event_Future &future);

    /// Waits for completion of all events, with a timeout
    bool wait_on_completion (ACE_Time_Value *tv);

    void completed_events (Event_List &event_list);

  protected:
    virtual void on_all_completed ();

    virtual void on_all_completed_with_failure ();

    bool single_threaded_wait_on_completion (ACE_Time_Value *tv);

  private:
    Deployment_Scheduler &sched_;

    TAO_SYNCH_MUTEX mutex_;
    ACE_Condition< TAO_SYNCH_MUTEX > condition_;

    Event_List completed_events_;
  };

}

#include /**/ "ace/post.h"

#endif

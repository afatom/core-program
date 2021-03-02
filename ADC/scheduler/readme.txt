
		taskToExecute = HeapExtract(_scheduler->m_heap);
		assert(taskToExecute != NULL);
		isReschedule = TaskExecution((Task*)taskToExecute);
		/*take cpu time << actualy the time that takes to execute the task*/
		taskExecutionEndTime =  (size_t)(GetProcessorTime());
		if(isReschedule == TRUE)
		{
			execTask = (Task*)taskToExecute;
			TaskUpdateDueTime(&execTask, taskExecutionEndTime);
			/*push it to heap again*/
			HeapInsert(_scheduler->m_heap, taskToExecute);
		}
		/*if not we destroy it! dont return it to heap*/
		execTask = (Task*)taskToExecute;
		TaskDestroy(&execTask);


        	return EMPTY_BUFFER_ERROR;

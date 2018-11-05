//The functions here implements the timers for sending mail

#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>

class Timer
{
	std::thread Thread;
	bool alive = false;
	long callNum = -1L;
	long repeat_Count = -1L;
	std::chrono::milliseconds interval = std::chrono::milliseconds(0);
	std::function<void(void)> funct = nullptr;

	void SleepAndRun()
	{
		std::this_thread::sleep_for(interval);
		if (alive)
			Function()();
	}
	void ThreadFunc()
	{
		if (callNum == Infinite)
		{
			while (alive)
			{
				SleepAndRun();
			}
		}
		else {
			while (repeat_Count--)
			{
				SleepAndRun();
			}
		}
	}
public:
	static const long Infinite = -1L;
	
	Timer() {

	}
	Timer(const std::function<void(void)> &f):funct(f){}
	
	Timer(const std::function<void(void)> &f,
		const unsigned long &i,
		const long repeat = Timer::Infinite):funct(f),
		interval(std::chrono::milliseconds(i)),
		callNum(repeat){}
	void Start(bool Async = true)
	{
		if (IsAlive())
			return;
		alive = true;
		repeat_Count = callNum;
		if (Async)
			Thread = std::thread(&Timer::ThreadFunc, this);
		
		else
			this->ThreadFunc();
	}
	void Stop()
	{
		alive = false;
		Thread.join();
	}
	void SetFunction(const std::function<void(void)> &f)
	{
		funct = f;
	}
	bool IsAlive() const { return alive; }
	void RepeatCount(const long r)
	{
		if (alive)
			return;
		callNum = r;
	}
	long GetLeftCount() const { return repeat_Count; }
	long RepeatCount() const { return callNum; }
	void SetInterval(const unsigned long &i)
	{
		if (alive)
			return;
		interval = std::chrono::milliseconds(i);
	}
	unsigned long Interval() const { return interval.count(); }
	const std::function<void(void)> &Function() const
	{
		return funct;
	}
};

#endif

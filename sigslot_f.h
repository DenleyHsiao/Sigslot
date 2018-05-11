#ifndef __SIGSLOT_F__
#define __SIGSLOT_F__ 

#include "sigslot.h"
#include <cassert>

namespace sigslot {
	template<class mt_policy, typename... Args>
	class _signal_f : public _signal_base<mt_policy>
	{
	public:
		typedef typename std::list<_connection_base<mt_policy, Args...> *>  connections_list;
		_signal_f() = default;
    
		_signal_f(const _signal_f<mt_policy, Args...>& s) : _signal_base<mt_policy>(s)
		{
			lock_block<mt_policy> lock(this);
			for(auto slot: m_connected_slots)
			{
				m_connected_slots.push_back(slot->clone());
			}
		}
    
		void slot_duplicate(const has_slots<mt_policy>* oldtarget, has_slots<mt_policy>* newtarget)
		{
			lock_block<mt_policy> lock(this);
			for(auto slot: m_connected_slots)
			{
				if(slot->getdest() == oldtarget)
				{
					m_connected_slots.push_back(slot->duplicate(newtarget));
				}
			}
		}
    
		~_signal_f()
		{
			disconnect_all();
		}
    
		void disconnect_all()
		{
			lock_block<mt_policy> lock(this);
			for(auto slot: m_connected_slots)
			{
				delete slot;
			}
        
			m_connected_slots.erase(m_connected_slots.begin(), m_connected_slots.end());
		}
    
		void disconnect(has_slots<mt_policy>* pclass)
		{
			lock_block<mt_policy> lock(this);
			for(auto slot: m_connected_slots)
			{
				if(slot->getdest() == pclass)
				{
					delete slot;
					m_connected_slots.remove(slot);
					pclass->signal_disconnect(this);
					break;
				}
			}
		}
    
		void slot_disconnect(has_slots<mt_policy>* pslot)
		{
			lock_block<mt_policy> lock(this);
	        auto itEnd = m_connected_slots.end();
			for(auto it = m_connected_slots.begin(); it != itEnd; ++it)
			{
	            if((*it)->getdest() == pslot)
				{
	                delete *it;
	                m_connected_slots.erase(it);
				}
			}
		}
    
	protected:
		connections_list m_connected_slots;   
	};

	template<class mt_policy, typename... Args>
	class _connection_f : public _connection_base<mt_policy, Args...>
	{
	public:
		_connection_f(std::function<void(Args...)> pfun)
			: m_pfun(pfun)
		{
		}
    
		virtual _connection_base<mt_policy, Args...>* clone()
		{
			assert(false);
			return nullptr; //new _connection_f<mt_policy, Args...>(*this);
		}
    
		virtual _connection_base<mt_policy, Args...>* duplicate(has_slots<mt_policy>* pnewdest)
		{
			assert(false);
			return nullptr; //new _connection_f<mt_policy, Args...>(m_pfun);
		}
    
		virtual void emit(Args... args)
		{
			m_pfun(args...);
		}
    
		virtual has_slots<mt_policy>* getdest() const
		{
			assert(false);
			return nullptr;
		}

	private:
		std::function<void(Args...)> m_pfun;
	};

	template<class mt_policy, typename... Args>
	class signal_f : public _signal_f<mt_policy, Args...>
	{
	public:
		signal_f() = default;
    
		signal_f(const signal_f<mt_policy, Args...>& s) : _signal_f<mt_policy>(s)
		{
			;
		}
    
	    void connect(std::function<void(Args...)> pfun)
		{
			lock_block<mt_policy> lock(this);
			auto conn = new _connection_f<mt_policy, Args...>(pfun);
			this->m_connected_slots.push_back(conn);
		}
    
		void emit(Args... args)
		{
			lock_block<mt_policy> lock(this);
			for(auto slot: this->m_connected_slots)
			{    
				slot->emit(args...);
	        }
		}
    
		void operator()(Args... args)
		{
			emit(args...);
		}
	};

	template <typename... Args>
	using signal_fd = signal_f<SIGSLOT_DEFAULT_MT_POLICY, Args...>;
}

#endif
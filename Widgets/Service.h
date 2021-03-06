/*****************************************************************************/
/*!
\file Service.h
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#ifndef SERVICE_H
#define SERVICE_H

#include <cassert>
#include <memory>

namespace Data
{
	template
		<typename Serv, typename Deleter = std::default_delete<Serv>>
	class Service
	{
	public:

		template <typename... TArgs>
		static Serv& Register(TArgs&& ...args)
		{
			assert(mService == nullptr);
			mService = std::make_unique<Serv>
				(std::forward<TArgs>(args)...);
			return *mService;
		}
		static bool Exist()
		{
			return (&*mService) != nullptr;
		}
		static Serv& Get()
		{
			assert(mService);
			return *mService;
		}
		static void Release()
		{
			assert(mService);
			mService.reset(nullptr);
		}
	private:
		inline static std::unique_ptr<Serv, Deleter> mService;
	};
}
#endif
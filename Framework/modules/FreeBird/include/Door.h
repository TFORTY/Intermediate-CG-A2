#pragma once

namespace freebird
{
	class Door {

	public:
		Door();

		void Update();

		void SetOpen(bool open);
		bool GetOpen();

	private:
		bool isOpen;
	};
}

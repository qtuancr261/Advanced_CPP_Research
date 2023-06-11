#include <iostream>

class Message final {
private:
	int _id;

public:
	Message();
	Message(int initId);
	Message(const Message& other);
	~Message();

	/// @brief
	/// @return current message ID
	int getId() const;
};
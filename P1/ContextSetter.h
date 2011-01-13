#ifndef CONTEXTSETTER_H_83FBBAA8_1C39_454E_BA8A_7C9ECC09E72E
#define CONTEXTSETTER_H_83FBBAA8_1C39_454E_BA8A_7C9ECC09E72E

namespace Prototype1{
	namespace Internal{
		class ClassContext;
	}
	class ContextSetter{
	protected:
		virtual ~ContextSetter(){}
	private:
		friend class Prototype1::Internal::ClassContext;
		virtual void setContext(Prototype1::Internal::ClassContext*)=0;
	};
}

#endif // CONTEXTSETTER_H_83FBBAA8_1C39_454E_BA8A_7C9ECC09E72E

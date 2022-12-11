// Copyright 2020 Scott Brauer
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

///
/// \file   ConnectionOptionElements.hpp
/// \author Scott Brauer
/// \date   Apr 9, 2020
///
/// \brief Base classes used by the ConnectionOptions classes
///

#ifndef LIB_AMQP_INCLUDE_OFFCENTER_AMQP_CONNECTIONOPTIONELEMENTS_HPP_
#define LIB_AMQP_INCLUDE_OFFCENTER_AMQP_CONNECTIONOPTIONELEMENTS_HPP_

//#include <vector>
//#include <string>
//#include <sstream>
//#include <climits>
//#include <initializer_list>

#include "offcenter/common/RuntimeException.hpp"

namespace offcenter {
namespace amqp {

template<typename InputIt>
std::string join(InputIt begin,
				 InputIt end,
				 const std::string & separator,
				 const std::string & concluder)
{
	std::ostringstream ss;

	if(begin != end) {
		ss << *begin++;
	}

	while(begin != end) {
		ss << separator;
		ss << *begin++;
	}

	ss << concluder;
	return ss.str();
}

/**
 *
 */
template<typename T>
std::string joinUri(const std::initializer_list<T> &v)
{
	return join(v.begin(), v.end());
};

/// Base interface for all option elements
class IInternalElement {
public:
	virtual ~IInternalElement() = default;

	/// Return the URI text for this option element
	/// \return \<key\>=\<value\>
	virtual const std::string uriText() const = 0;

	/// Has the option element changed from it's default value
	/// \retval true Option element has changed
	virtual bool isDirty() const = 0;

protected:
	IInternalElement() = default;
};

/// Basic implementation for all option elements
/// \tparam T Type of value
template<typename T>
class InternalElement : public IInternalElement {
public:
	InternalElement() = delete;

	/// Initialize the base for all option elements
	/// \param[in] key The text used when creating the URI text for this option element (i.e. \<key\>=\<value\>)
	explicit InternalElement(const std::string &key):
		IInternalElement(),
		m_key(key),
		m_value(),
		m_dirty(false) {}

	/// Initialize the base for all option elements
	/// \param[in] key The text used when creating the URI text for this element (i.e. \<key\>=\<value\>)
	/// \param[in] initialValue The default value for this option element
	explicit InternalElement(const std::string &key, const T initialValue):
		IInternalElement(),
		m_key(key),
		m_value(initialValue),
		m_dirty(false) {}

	virtual ~InternalElement() = default;

	/// \copybrief offcenter::amqp::IInternalElement::uriText()
	/// \return \a \<key\>=\<value\> will be returned if the value has changed from it's default value (i.e. isDirty() == true).
	/// Otherwise an empty string will be returned.
	const std::string uriText() const override {
		if (m_dirty) {
			std::ostringstream oss;
			oss << m_key << "=" << valueAsText();
			return oss.str();
		}
		return "";
	}

	/// Simple assignment operator for value.
	/// If the value is different than the previous value, mark as dirty.
	/// \param value New value for option element
	void operator()(const T &value) {
		if (m_value != value) {
			m_value = value;
			m_dirty = true;
		}
	}

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	InternalElement& operator=(const T &value){
		this->operator()(value);
		return *this;
	}

	/// Return the current value
	/// \return Current value
	T value() const{
		return m_value;
	}

	/// \copydoc offcenter::amqp::IInternalElement::isDirty()
	bool isDirty() const override { return m_dirty; }

	/// Value as std::string
	/// \return A string representation for the value
	virtual const std::string valueAsText() const {
		std::ostringstream oss;
		oss << m_value;
		return oss.str();
	}

private:
	T m_value;
	const std::string m_key;
	bool m_dirty;
};

/// Internal option element defined with an initial value used to determine when dirty
/// \tparam T Type of value
/// \tparam INITIAL_VALUE Initial value
/// \note This class will work only with valid template non-type parameters. Refer to the \link offcenter::amqp::DoubleElement DoubleElement \endlink for an
///       example using an invalid template non-type parameter.
template<typename T, T INITIAL_VALUE>
class InternalElementWithDefault : public InternalElement<T> {
public:
	InternalElementWithDefault() = delete;

	/// Initialize the base for option elements that have a default value
	/// \param[in] key The text used when creating the URI text for this option element (i.e. \<key\>=\<value\>)
	explicit InternalElementWithDefault(const std::string &key):
		InternalElement<T>(key, INITIAL_VALUE) {}
	virtual ~InternalElementWithDefault() = default;

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	InternalElementWithDefault& operator=(const T &value){
		InternalElement<T>::operator=(value);
		return *this;
	}
};

/// Boolean option element defined with an initial value used to determine when dirty
/// \tparam INITIAL_VALUE Initial value
template<bool INITIAL_VALUE>
class BooleanElement : public InternalElementWithDefault<bool, INITIAL_VALUE> {
public:
	BooleanElement() = delete;

	/// Initialize the boolean option element
	/// \param[in] key The text used when creating the URI text for this option element (i.e. \<key\>=\<value\>)
	explicit BooleanElement(const std::string &key) :
		InternalElementWithDefault<bool, INITIAL_VALUE>(key) {}

	virtual ~BooleanElement() = default;

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	BooleanElement& operator=(const bool &value){
		InternalElementWithDefault<bool, INITIAL_VALUE>::operator=(value);
		return *this;
	}

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	BooleanElement& operator=(const BooleanElement& value){
		InternalElementWithDefault<bool, INITIAL_VALUE>::operator=(value.value());
		return *this;
	}

	/// Value as std::string
	/// \return A string representation for the value ("true" or "false")
	virtual const std::string valueAsText() const {
		std::ostringstream oss;
		oss << std::boolalpha << InternalElement<bool>::value();
		return oss.str();
	}
};

/// Integer option element defined with an initial value used to determine when dirty
/// \tparam INITIAL_VALUE Initial value
template<int INITIAL_VALUE>
class IntegerElement : public InternalElementWithDefault<int, INITIAL_VALUE> {
public:
	IntegerElement() = delete;

	/// Initialize the integer option element
	/// \param[in] key The text used when creating the URI text for this option element (i.e. \<key\>=\<value\>)
	explicit IntegerElement(const std::string &key) :
		InternalElementWithDefault<int, INITIAL_VALUE>(key) {}

	virtual ~IntegerElement() = default;

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	IntegerElement<INITIAL_VALUE>& operator=(const int &value){
		InternalElementWithDefault<int, INITIAL_VALUE>::operator=(value);
		return *this;
	}

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	IntegerElement<INITIAL_VALUE>& operator=(const IntegerElement<INITIAL_VALUE>& value){
		InternalElementWithDefault<int, INITIAL_VALUE>::operator=(value.value());
		return *this;
	}
};

/// Double option element
class DoubleElement : public InternalElement<double> {
public:
	DoubleElement() = delete;

	/// Initialize the double option element
	/// \param[in] key The text used when creating the URI text for this option element (i.e. \<key\>=\<value\>)
	/// \param[in] initialValue The initial value
	explicit DoubleElement(const std::string &key, const double &initialValue) :
		InternalElement<double>(key, initialValue) {}

	virtual ~DoubleElement() = default;

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	DoubleElement& operator=(const double &value){
		InternalElement<double>::operator=(value);
		return *this;
	}

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	DoubleElement& operator=(const DoubleElement &value){
		InternalElement<double>::operator=(value.value());
		return *this;
	}
};

/// Wire format protocol
enum WireFormat {
	stomp,   ///< is the native protocol that Apache ActiveMQ uses. It is designed for performance and size on the wire -
			 /// sacrificing some ease of implementation with higher performance and reduced network bandwidth as a priority.
			 /// OpenWire was first released in Apache ActiveMQ 4.0.
	openwire ///< is a simpler text based protocol which is designed to be very simple to implement in a few hours in any language
			 /// or platform (e.g. you can use a telnet client to communicate via Stomp). A Stomp client is not going to be as
			 /// efficient as an client that uses OpenWire, but it much simpler so you can generally be up and running with it much quicker.
};

/// Wire format option element
class WireFormatElement : public InternalElement<WireFormat> {
public:
	WireFormatElement() = delete;

	/// Initialize the wire format option element
	/// \param[in] key The text used when creating the URI text for this option element (i.e. \<key\>=\<value\>)
	/// \param[in] initialValue The initial value
	explicit WireFormatElement(const std::string &key, WireFormat initialValue) :
		InternalElement<WireFormat>(key, initialValue) {}

	virtual ~WireFormatElement() {}

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	WireFormatElement& operator=(const WireFormatElement &value){
		InternalElement<WireFormat>::operator=(value.value());
		return *this;
	}

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	WireFormatElement& operator=(const WireFormat &value){
		InternalElement<WireFormat>::operator=(value);
		return *this;
	}

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	WireFormatElement& operator=(const std::string &value){
		static std::map<std::string, WireFormat> lookup = {
				{"stomp", WireFormat::stomp},
				{"openwire", WireFormat::openwire}
		};

		try {
			std::string wireFormat = value;
			boost::algorithm::to_lower(wireFormat);
			InternalElement<WireFormat>::operator=(lookup.at(wireFormat));
		} catch(std::out_of_range& e) {
			std::string msg("Unknown wire format string (");
			msg += value;
			msg += ")";
			throw offcenter::common::RuntimeException(msg);
		}

		return *this;
	}

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	WireFormatElement& operator()(const std::string &value){
		return operator=(value);
	}


	/// Value as std::string
	/// \return A string representation for the value ("stomp" or "openwire")
	virtual const std::string valueAsText() const {
		switch(InternalElement<WireFormat>::value()) {
			case WireFormat::stomp:
				return "stomp";
			case WireFormat::openwire:
				return "openwire";
		}
		return "";
	}
};

/// String option element
class StringElement : public InternalElement<std::string> {
public:
	StringElement() = delete;

	/// Initialize the string option element
	/// \param[in] key The text used when creating the URI text for this option element (i.e. \<key\>=\<value\>)
	/// \param[in] initialValue The initial value
	StringElement(const std::string &key, const std::string &initialValue) :
		InternalElement<std::string>(key, initialValue) {}

	virtual ~StringElement() {}

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	StringElement& operator=(const std::string &value){
		InternalElement<std::string>::operator=(value);
		return *this;
	}

	/// \copydoc offcenter::amqp::InternalElement::operator()(const T &value)
	StringElement& operator=(const StringElement &value){
		InternalElement<std::string>::operator=(value.value());
		return *this;
	}
};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* LIB_AMQP_INCLUDE_OFFCENTER_AMQP_CONNECTIONOPTIONELEMENTS_HPP_ */

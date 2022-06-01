#ifndef DATATYPE_BENCHMARKS_PROJECT_CerealWRITEABLE_H
#define DATATYPE_BENCHMARKS_PROJECT_CerealWRITEABLE_H

#include <utility>
#include <memory>
#include <iostream>
#include <cereal/cereal.hpp>
namespace semantic_type {

    class CerealWriteable {
    public:
        template<typename T> CerealWriteable(T && value) : pimpl_{new CerealWriteableModel<T>(std::forward<T>(value))} {};

        CerealWriteable(CerealWriteable const& writeable) : pimpl_{writeable.pimpl_->Clone()} {};

        CerealWriteable& operator=(CerealWriteable const& right) {
            if (this == &right)
                return *this;
            pimpl_ = right.pimpl_->Clone();

            return *this;
        };
        CerealWriteable(CerealWriteable && pose) = default;
        CerealWriteable& operator=(CerealWriteable && pose) = default;


    private:
        struct CerealWriteableConcept {
            virtual ~CerealWriteableConcept() {};
            virtual std::unique_ptr<CerealWriteableConcept> Clone() const = 0;

            virtual std::ostream& WriteDataInternal(std::ostream& stream) const = 0;


        };

        template<typename T>
        struct CerealWriteableModel : CerealWriteableConcept {
            CerealWriteableModel(T&& value) : value_{std::forward<T>(value)} {}

            std::unique_ptr<CerealWriteableConcept> Clone() const override {
                return std::make_unique<CerealWriteableModel<T> >(*this);
            };

            std::ostream &WriteDataInternal(std::ostream &stream) const override {
                return WriteData(value_, stream);
            }

            T value_;
        };


            friend std::ostream& CerealWrite(const CerealWriteable & value, std::ostream& stream) {
                return value.pimpl_->WriteDataInternal(stream);
            }

        std::unique_ptr<CerealWriteableConcept> pimpl_;
    };




} // semantic_type

#endif //DATATYPE_BENCHMARKS_PROJECT_CerealWRITEABLE_H

/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) 2008-2016, Alliance for Sustainable Energy, LLC. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 *  following conditions are met:
 *
 *  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *  disclaimer.
 *
 *  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *  following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote
 *  products derived from this software without specific prior written permission from the respective party.
 *
 *  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative
 *  works may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without
 *  specific prior written permission from Alliance for Sustainable Energy, LLC.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER, THE UNITED STATES GOVERNMENT, OR ANY CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

#ifndef PROJECT_VAGRANTSETTINGSRECORD_IMPL_HPP
#define PROJECT_VAGRANTSETTINGSRECORD_IMPL_HPP

#include "ProjectAPI.hpp"
#include "CloudSettingsRecord_Impl.hpp"

namespace openstudio {

class VagrantSettings;

namespace project {

class UrlRecord;

namespace detail {

  /** VagrantSettingsRecord_Impl is a CloudSettingsRecord_Impl that is the implementation class for VagrantSettingsRecord.*/
  class PROJECT_API VagrantSettingsRecord_Impl : public CloudSettingsRecord_Impl {
   public:
    /** @name Constructors and Destructors */
    //@{

    VagrantSettingsRecord_Impl(const VagrantSettings& vagrantSettings,
                               ProjectDatabase& database);

    /** Constructor from query. Throws if bad query. */
    VagrantSettingsRecord_Impl(const QSqlQuery& query, ProjectDatabase& database);

    virtual ~VagrantSettingsRecord_Impl() {}

    //@}
    /** @name Virtual Methods */
    //@{

    /** Returns objects directly owned by this Record. Children are removed when this Record 
     *  is removed. */
    virtual std::vector<ObjectRecord> children() const override;

    /** Save the row that corresponds to this record in projectDatabase. */
    virtual void saveRow(const std::shared_ptr<QSqlDatabase> &database) override;

    //@}
    /** @name Getters */
    //@{

    UrlRecord serverUrlRecord() const;

    UrlRecord workerUrlRecord() const;

    virtual CloudSettings cloudSettings() const override;

    VagrantSettings vagrantSettings() const;

    //@}
        /** @name Setters */
    //@{

    /** Impl-only method. Reverts record id values back to last state. For use in constructor
     *  so can access old related records for comparison and possible removal. */
    void revertToLastRecordIds();

    /** Impl-only method. */
    void setServerUrlRecordId(int id);

    /** Impl-only method. */
    void setWorkerUrlRecordId(int id);

    //@}
   protected:
    /** Bind data member values to a query for saving. */
    virtual void bindValues(QSqlQuery& query) const override;

    /** Set the last state of this object from the query (including id). */
    virtual void setLastValues(const QSqlQuery& query, ProjectDatabase& projectDatabase) override;

    /** Check that values (except id) are same as query. */
    virtual bool compareValues(const QSqlQuery& query) const override;

    /** Save values to last state. */
    virtual void saveLastValues() override;

    /** Revert values back to last state. */
    virtual void revertToLastValues() override;

   private:
    REGISTER_LOGGER("openstudio.project.VagrantSettingsRecord");

    bool m_userAgreementSigned;
    openstudio::path m_serverPath;
    int m_serverUrlRecordId;
    openstudio::path m_workerPath;
    int m_workerUrlRecordId;
    bool m_haltOnStop;
    std::string m_username;

    bool m_lastUserAgreementSigned;
    openstudio::path m_lastServerPath;
    int m_lastServerUrlRecordId;
    openstudio::path m_lastWorkerPath;
    int m_lastWorkerUrlRecordId;
    bool m_lastHaltOnStop;
    std::string m_lastUsername;
  };

} // detail

} // project
} // openstudio

#endif // PROJECT_VAGRANTSETTINGSRECORD_IMPL_HPP

#pragma once

#include "RE/BSCore/BSFixedString.h"
#include "RE/BSCore/BSString.h"
#include "RE/FormComponents/Components/TESCondition.h"
#include "RE/FormComponents/Enums/FormTypes.h"
#include "RE/FormComponents/TESForm/TESForm.h"


namespace RE
{
	class NiFormArray;


	struct IDLE_DATA  // DATA
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kParent = 1 << 0,
			kSequence = 1 << 1,
			kNoAttacking = 1 << 2,
			kBlocking = 1 << 3
		};


		// members
		std::int8_t							 loopMin;				   // 0
		std::int8_t							 loopMax;				   // 1
		stl::enumeration<Flag, std::uint8_t> flags;					   // 2
		std::uint8_t						 animationGroupSelection;  // 3
		std::uint16_t						 replayDelay;			   // 4
	};
	static_assert(sizeof(IDLE_DATA) == 0x6);


	class TESIdleForm : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESIdleForm;
		inline static constexpr auto FORMTYPE = FormType::Idle;


		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};


		virtual ~TESIdleForm();	 // 00

		// override (TESForm)
		virtual void		InitializeData() override;											// 04
		virtual void		ClearData() override;												// 05
		virtual bool		Load(TESFile* a_mod) override;										// 06
		virtual TESForm*	CreateDuplicateForm(bool a_createEditorID, void* a_arg2) override;	// 09
		virtual void		InitItemImpl() override;											// 13
		virtual const char* GetFormEditorID() const override;									// 32 - { return formEditorID.c_str(); }
		virtual bool		SetFormEditorID(const char* a_str) override;						// 33


		// members
		TESCondition  conditions;	  // 20
		IDLE_DATA	  data;			  // 28 - DATA
		std::uint16_t pad2E;		  // 2E
		NiFormArray*  childIdles;	  // 30
		TESIdleForm*  parentIdle;	  // 38 - ANAM~
		TESIdleForm*  prevIdle;		  // 40 - ~ANAM
		BSFixedString animFileName;	  // 48 - DNAM
		BSFixedString animEventName;  // 50 - ENAM
		BSString	  formEditorID;	  // 58 - EDID
	};
	static_assert(sizeof(TESIdleForm) == 0x68);
}
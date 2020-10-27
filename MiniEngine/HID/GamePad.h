/*!
*@brief	パッド
*/

#pragma once

	
/*!
	*@brief	仮想ボタン定義。
	*/
enum class EnButton : int {
	enButtonUp,		//!<上。
	enButtonDown,		//!<下。
	enButtonLeft,		//!<左。
	enButtonRight,		//!<右。
	enButtonA,			//!<Aボタン。
	enButtonB,			//!<Bボタン。
	enButtonX,			//!<Xボタン。
	enButtonY,			//!<Yボタン。
	enButtonSelect,	//!<セレクトボタン。
	enButtonStart,		//!<スタートボタン。
	enButtonRB1,		//!<RB1ボタン。
	enButtonRB2,		//!<RB2ボタン。
	enButtonRB3,		//!<RB3ボタン。
	enButtonLB1,		//!<LB1ボタン。
	enButtonLB2,		//!<LB2ボタン。
	enButtonLB3,		//!<LB3ボタン。
	enButtonNum,	//!<ボタンの数。
};
/*!
*@brief	パッド
*/
class GamePad {
public:
	static const int CONNECT_PAD_MAX = 4;		//接続可能なパッドの最大数。
	/*!
		*@brief	パッドステート。
		*/
	struct PAD_STATE
	{
		XINPUT_STATE state;
		bool bConnected;
	};
	/*!
		*@brief	コンストラクタ。
		*/
	GamePad();
	/*!
		*@brief	デストラクタ。
		*/
	~GamePad();
	/*!
	*@brief	初期化。
	*@param[in]	padNo	パッド番号。
	*/
	void Init(int padNo)
	{
		m_padNo = padNo;
	}
	/*!
	*@brief	更新。
	*/
	void Update();
	/*!
	*@brief	ボタンのトリガー判定。
	*@return	trueが返ってきたらトリガー入力。
	*/
	bool IsTrigger(EnButton button) const
	{
		return m_trigger[static_cast<int>(button)] != 0;
	}
	/*!
	*@brief	ボタンが押されているか判定。
	*@return	trueが返ってきたら押されている。
	*/
	bool IsPress(EnButton button) const
	{
		return m_press[static_cast<int>(button)] != 0;
	}
	/*!
	*@brief	何かのボタンが押されているか判定
	*@return	trueが返ってきたら押されている。
	*/
	bool IsPressAnyKey() const
	{
		return IsPress(EnButton::enButtonUp)
			|| IsPress(EnButton::enButtonDown)
			|| IsPress(EnButton::enButtonLeft)
			|| IsPress(EnButton::enButtonRight)
			|| IsPress(EnButton::enButtonA)
			|| IsPress(EnButton::enButtonB)
			|| IsPress(EnButton::enButtonX)
			|| IsPress(EnButton::enButtonY)
			|| IsPress(EnButton::enButtonSelect)
			|| IsPress(EnButton::enButtonStart)
			|| IsPress(EnButton::enButtonRB1)
			|| IsPress(EnButton::enButtonRB2)
			|| IsPress(EnButton::enButtonRB3)
			|| IsPress(EnButton::enButtonLB1)
			|| IsPress(EnButton::enButtonLB2)
			|| IsPress(EnButton::enButtonLB3);
	}
	/*!
	*@brief	左スティックのX軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetLStickXF() const
	{
		return m_lStickX;
	}
	/*!
	*@brief	左スティックのY軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetLStickYF() const
	{
		return m_lStickY;
	}
	/*!
	*@brief	右スティックのX軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetRStickXF() const
	{
		return m_rStickX;
	}
	/*!
	*@brief	右スティックのY軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetRStickYF() const
	{
		return m_rStickY;
	}
	//フレームの開始時に呼ばれる関数。
	static void BeginFrame();
public:
	enum { MAX_PAD = 4 };
	enum class EnXInputPadState {
		Undef,		//不明。
		Connect,	//接続されている。
		Disconnect,	//接続されていない。
	};
private:
	PAD_STATE m_state;	//!<パッドステート。
	int m_padNo = 0;			//!<パッド番号。
	int m_trigger[static_cast<int>(EnButton::enButtonNum)];	//!<トリガー入力のフラグ。
	int m_press[static_cast<int>(EnButton::enButtonNum)];	//!<press入力のフラグ。
	float m_lStickX = 0.0f;		//!<左スティックのX軸の入力量。
	float m_lStickY = 0.0f;		//!<左スティックのY軸の入力量。
	float m_rStickX = 0.0f;		//!<右スティックのX軸の入力量。
	float m_rStickY = 0.0f;		//!<右スティックのY軸の入力量。

	static EnXInputPadState m_padStates[MAX_PAD];
};

extern std::array<GamePad*, GamePad::CONNECT_PAD_MAX> g_pad;
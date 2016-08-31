/*
 * Qualcomm/Atheros WiSoCs DRAM related functions and defines
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _QCA_DRAM_H_
#define _QCA_DRAM_H_

/*
 * Prepare DDR SDRAM mode register value
 * For now use always burst length == 8
 */
#define DDR_SDRAM_MR_BURST_LEN_SHIFT		0
#define DDR_SDRAM_MR_BURST_LEN_MASK		BITS(DDR_SDRAM_MR_BURST_LEN_SHIFT, 3)
#define DDR_SDRAM_MR_BURST_INTERLEAVE_SHIFT	3
#define DDR_SDRAM_MR_BURST_INTERLEAVE_MASK	(1 << DDR_SDRAM_MR_BURST_INTERLEAVE_SHIFT)
#define DDR_SDRAM_MR_CAS_LAT_SHIFT		4
#define DDR_SDRAM_MR_CAS_LAT_MASK		BITS(DDR_SDRAM_MR_CAS_LAT_SHIFT, 3)
#define DDR_SDRAM_MR_DLL_RESET_SHIFT		8
#define DDR_SDRAM_MR_DLL_RESET_MASK		(1 << DDR_SDRAM_MR_DLL_RESET_SHIFT)
#define DDR_SDRAM_MR_WR_RECOVERY_SHIFT		9
#define DDR_SDRAM_MR_WR_RECOVERY_MASK		BITS(DDR_SDRAM_MR_WR_RECOVERY_SHIFT, 3)

#define _ddr_sdram_mr_val(_burst_i, \
			  _cas_lat, \
			  _dll_res, \
			  _wr_rcov) \
				    \
	((0x3            << DDR_SDRAM_MR_BURST_LEN_SHIFT)   & DDR_SDRAM_MR_BURST_LEN_MASK)   |\
	((_cas_lat       << DDR_SDRAM_MR_CAS_LAT_SHIFT)     & DDR_SDRAM_MR_CAS_LAT_MASK)     |\
	((_dll_res       << DDR_SDRAM_MR_DLL_RESET_SHIFT)   & DDR_SDRAM_MR_DLL_RESET_MASK)   |\
	(((_wr_rcov - 1) << DDR_SDRAM_MR_WR_RECOVERY_SHIFT) & DDR_SDRAM_MR_WR_RECOVERY_MASK) |\
	((_burst_i       << DDR_SDRAM_MR_BURST_INTERLEAVE_SHIFT) & DDR_SDRAM_MR_BURST_INTERLEAVE_MASK)

/* Prepare DDR SDRAM extended mode register value */
#define DDR_SDRAM_EMR_DLL_EN_SHIFT		0
#define DDR_SDRAM_EMR_DLL_EN_MASK		(1 << DDR_SDRAM_EMR_DLL_EN_SHIFT)
#define DDR_SDRAM_EMR_WEAK_STRENGTH_SHIFT	1
#define DDR_SDRAM_EMR_WEAK_STRENGTH_MASK	(1 << DDR_SDRAM_EMR_WEAK_STRENGTH_SHIFT)
#define DDR_SDRAM_EMR_OCD_PRG_SHIFT		7
#define DDR_SDRAM_EMR_OCD_PRG_MASK		BITS(DDR_SDRAM_EMR_OCD_PRG_SHIFT, 3)
#define DDR_SDRAM_EMR_OCD_EXIT_VAL		0
#define DDR_SDRAM_EMR_OCD_DEFAULT_VAL		7
#define DDR_SDRAM_EMR_NDQS_DIS_SHIFT		10
#define DDR_SDRAM_EMR_NDQS_DIS_MASK		(1 << DDR_SDRAM_EMR_NDQS_DIS_SHIFT)
#define DDR_SDRAM_EMR_RDQS_EN_SHIFT		11
#define DDR_SDRAM_EMR_RDQS_EN_MASK		(1 << DDR_SDRAM_EMR_RDQS_EN_SHIFT)
#define DDR_SDRAM_EMR_OBUF_DIS_SHIFT		12
#define DDR_SDRAM_EMR_OBUF_DIS_MASK		(1 << DDR_SDRAM_EMR_OBUF_DIS_SHIFT)

#define _ddr_sdram_emr_val(_dll_dis,  \
			   _drv_weak, \
			   _ocd_prg,  \
			   _ndqs_dis, \
			   _rdqs_en,  \
			   _obuf_dis) \
				      \
	((_dll_dis  << DDR_SDRAM_EMR_DLL_EN_SHIFT)   & DDR_SDRAM_EMR_DLL_EN_MASK)   |\
	((_ocd_prg  << DDR_SDRAM_EMR_OCD_PRG_SHIFT)  & DDR_SDRAM_EMR_OCD_PRG_MASK)  |\
	((_ndqs_dis << DDR_SDRAM_EMR_NDQS_DIS_SHIFT) & DDR_SDRAM_EMR_NDQS_DIS_MASK) |\
	((_rdqs_en  << DDR_SDRAM_EMR_RDQS_EN_SHIFT)  & DDR_SDRAM_EMR_RDQS_EN_MASK)  |\
	((_obuf_dis << DDR_SDRAM_EMR_OBUF_DIS_SHIFT) & DDR_SDRAM_EMR_OBUF_DIS_MASK) |\
	((_drv_weak << DDR_SDRAM_EMR_WEAK_STRENGTH_SHIFT) & DDR_SDRAM_EMR_WEAK_STRENGTH_MASK)

/* Prepare DDR SDRAM extended mode register 2 value */
#define DDR_SDRAM_EMR2_PASR_SHIFT	0
#define DDR_SDRAM_EMR2_PASR_MASK	BITS(DDR_SDRAM_EMR2_PASR_SHIFT, 3)
#define DDR_SDRAM_EMR2_DCC_EN_SHIFT	3
#define DDR_SDRAM_EMR2_DCC_EN_MASK	(1 << DDR_SDRAM_EMR2_DCC_EN_SHIFT)
#define DDR_SDRAM_EMR2_SRF_EN_SHIFT	7
#define DDR_SDRAM_EMR2_SRF_EN_MASK	(1 << DDR_SDRAM_EMR2_SRF_EN_SHIFT)

#define _ddr_sdram_emr2_val(_pasr,   \
			    _dcc_en, \
			    _srf_en) \
				     \
	((_pasr   << DDR_SDRAM_EMR2_PASR_SHIFT)   & DDR_SDRAM_EMR2_PASR_MASK)   |\
	((_dcc_en << DDR_SDRAM_EMR2_DCC_EN_SHIFT) & DDR_SDRAM_EMR2_DCC_EN_MASK) |\
	((_srf_en << DDR_SDRAM_EMR2_SRF_EN_SHIFT) & DDR_SDRAM_EMR2_SRF_EN_MASK)

/*
 * DDR timing related controller register values
 */

/* DDR_CONFIG */
#define _qca_ddr_cfg_reg_val(_tras,  \
			     _trcd,  \
			     _trp,   \
			     _trrd,  \
			     _trfc,  \
			     _tmrd,  \
			     _cas,   \
			     _opage) \
				     \
	((_tras  << QCA_DDR_CFG_TRAS_SHIFT)       & QCA_DDR_CFG_TRAS_MASK)       |\
	((_trcd  << QCA_DDR_CFG_TRCD_SHIFT)       & QCA_DDR_CFG_TRCD_MASK)       |\
	((_trp   << QCA_DDR_CFG_TRP_SHIFT)        & QCA_DDR_CFG_TRP_MASK)        |\
	((_trrd  << QCA_DDR_CFG_TRRD_SHIFT)       & QCA_DDR_CFG_TRRD_MASK)       |\
	((_trfc  << QCA_DDR_CFG_TRFC_SHIFT)       & QCA_DDR_CFG_TRFC_MASK)       |\
	((_tmrd  << QCA_DDR_CFG_TMRD_SHIFT)       & QCA_DDR_CFG_TMRD_MASK)       |\
	((_cas   << QCA_DDR_CFG_CAS_3LSB_SHIFT)   & QCA_DDR_CFG_CAS_3LSB_MASK)   |\
	((_opage << QCA_DDR_CFG_PAGE_CLOSE_SHIFT) & QCA_DDR_CFG_PAGE_CLOSE_MASK) |\
	(((_cas & 0x8) >> 3) << QCA_DDR_CFG_CAS_MSB_SHIFT)

/* DDR_CONFIG2 */
#define _qca_ddr_cfg2_reg_val(_burst_type, \
			      _ctrl_oe_en, \
			      _phase_sel,  \
			      _cke,        \
			      _twr,        \
			      _trtw,       \
			      _trtp,       \
			      _twtr,       \
			      _gate_lat,   \
			      _half_width) \
					   \
	(0x8          << QCA_DDR_CFG2_BURST_LEN_SHIFT)                                  |\
	((_burst_type << QCA_DDR_CFG2_BURST_TYPE_SHIFT) & QCA_DDR_CFG2_BURST_TYPE_MASK) |\
	((_ctrl_oe_en << QCA_DDR_CFG2_CTRL_OE_EN_SHIFT) & QCA_DDR_CFG2_CTRL_OE_EN_MASK) |\
	((_phase_sel  << QCA_DDR_CFG2_PHASE_SEL_SHIFT)  & QCA_DDR_CFG2_PHASE_SEL_MASK)  |\
	((_cke        << QCA_DDR_CFG2_CKE_SHIFT)        & QCA_DDR_CFG2_CKE_MASK)        |\
	((_twr        << QCA_DDR_CFG2_TWR_SHIFT)        & QCA_DDR_CFG2_TWR_MASK)        |\
	((_trtw       << QCA_DDR_CFG2_TRTW_SHIFT)       & QCA_DDR_CFG2_TRTW_MASK)       |\
	((_trtp       << QCA_DDR_CFG2_TRTP_SHIFT)       & QCA_DDR_CFG2_TRTP_MASK)       |\
	((_twtr       << QCA_DDR_CFG2_TWTR_SHIFT)       & QCA_DDR_CFG2_TWTR_MASK)       |\
	((_half_width << QCA_DDR_CFG2_HALF_WIDTH_LOW_SHIFT)    & QCA_DDR_CFG2_HALF_WIDTH_LOW_MASK) |\
	((_gate_lat   << QCA_DDR_CFG2_GATE_OPEN_LATENCY_SHIFT) & QCA_DDR_CFG2_GATE_OPEN_LATENCY_MASK)

/* DDR_DDR2_CONFIG */
#define _qca_ddr_ddr2_cfg_reg_val(_ddr2_en, \
				  _tfaw,    \
				  _twl)     \
					    \
	((_ddr2_en << QCA_DDR_DDR2_CFG_DDR2_EN_SHIFT)   & QCA_DDR_DDR2_CFG_DDR2_EN_MASK)   |\
	((_tfaw    << QCA_DDR_DDR2_CFG_DDR2_TFAW_SHIFT) & QCA_DDR_DDR2_CFG_DDR2_TFAW_MASK) |\
	((_twl     << QCA_DDR_DDR2_CFG_DDR2_TWL_SHIFT)  & QCA_DDR_DDR2_CFG_DDR2_TWL_MASK)

/*
 * DDR control functions
 */

/* Force MRS (mode register set) */
static inline void qca_dram_force_mrs(void)
{
	qca_soc_reg_write(QCA_DDR_CTRL_REG,
			  QCA_DDR_CTRL_FORCE_MRS_MASK);
}

/* Force EMRS (extended mode register set) */
static inline void qca_dram_force_emrs(void)
{
	qca_soc_reg_write(QCA_DDR_CTRL_REG,
			  QCA_DDR_CTRL_FORCE_EMRS_MASK);
}

/* Force EMR2S (extended mode register 2 set) */
static inline void qca_dram_force_emr2s(void)
{
	qca_soc_reg_write(QCA_DDR_CTRL_REG,
			  QCA_DDR_CTRL_FORCE_EMR2S_MASK);
}

/* Force EMR3S (extended mode register 3 set) */
static inline void qca_dram_force_emr3s(void)
{
	qca_soc_reg_write(QCA_DDR_CTRL_REG,
			  QCA_DDR_CTRL_FORCE_EMR3S_MASK);
}

/* Force auto refresh */
static inline void qca_dram_force_aref(void)
{
	qca_soc_reg_write(QCA_DDR_CTRL_REG,
			  QCA_DDR_CTRL_FORCE_AUTO_REFRESH_MASK);
}

/* Force precharge all */
static inline void qca_dram_force_preall(void)
{
	qca_soc_reg_write(QCA_DDR_CTRL_REG,
			  QCA_DDR_CTRL_FORCE_PRECHARGE_ALL_MASK);
}

/*
 * DDR setup related functions
 */

/* Sets DDR mode register value and issue MRS update */
static inline void qca_dram_set_mr(u32 value)
{
	qca_soc_reg_write(QCA_DDR_MR_REG, value);
	qca_dram_force_mrs();
}

/* Sets DDR extended mode register value and issue EMRS update */
static inline void qca_dram_set_emr(u32 value)
{
	qca_soc_reg_write(QCA_DDR_EMR_REG, value);
	qca_dram_force_emrs();
}

/* Sets DDR extended mode register 2 value and issue EMR2S update */
static inline void qca_dram_set_emr2(u32 value)
{
	qca_soc_reg_write(QCA_DDR_EMR2_REG, value);
	qca_dram_force_emr2s();
}

/* Sets DDR extended mode register 3 value and issue EMR3S update */
static inline void qca_dram_set_emr3(u32 value)
{
	qca_soc_reg_write(QCA_DDR_EMR3_REG, value);
	qca_dram_force_emr3s();
}

#endif /* _QCA_DRAM_H_ */

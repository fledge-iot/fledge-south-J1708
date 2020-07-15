#ifndef _J1708_H
#define _J1708_H
/*
 * Fledge south service plugin
 *
 * Copyright (c) 2020 Nex Computers Inc.
 *
 * Release under the Apache 2.0 License
 *
 * Author: Daniel Man
 */
#include <reading.h>
#include <config_category.h>
#include <thread>

class J1708 {
	public:
			J1708();
			~J1708();
			Reading		nextValue();
	void	setAssetName(const std::string& assetName)
		{
			m_asset = assetName;
		}
	void	setPort(const std::string& port)
		{
			m_port = port;
		}
	void	configure(ConfigCategory *config);
	void 	start();
	void	pollThread();
	void	registerIngest(void *data, void(*cb) (void *, Reading))
		{
			m_ingest = cb;
			m_data = data;
		}

	private:
		std::string	m_asset;
		std::string m_port;
		int			m_baud;
		int			m_bits;
		int			m_stopBits;
		char 		m_parity;
		FILE		*m_fp;
		std::thread	*m_thread;
		unsigned int m_sleepInterval;
		bool		m_running;
		void		*m_data;
		void		(*m_ingest)(void *, Reading);
};
#endif
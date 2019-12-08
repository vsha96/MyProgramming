token = '358566966:AAEIAY_9VCUGPGjrSQZ2a5n6IR7h20WeAuI'
API_URL = 'https://api.telegram.org/bot%s/sendMessage' % token

async def handler(request):
    data = await request.json()
    headers = {
        'Content-Type': 'application/json'
    }
    message = {
        'chat_id': data['message']['chat']['id'],
        'text': data['message']['text']
    }
    async with aiohttp.ClientSession(loop=loop) as session:
        async with session.post(API_URL,
                                data=json.dumps(message),
                                headers=headers) as resp:
            try:
                assert resp.status == 200
            except:
                return web.Response(status=500)
    return web.Response(status=200)

async def init_app(loop):
    app = web.Application(loop=loop, middlewares=[])
    app.router.add_post('/api/v1', handler)
    return app

if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    try:
        app = loop.run_until_complete(init_app(loop))
        web.run_app(app, host='0.0.0.0', port=8080)
    except Exception as e:
        print('Error create server: %r' % e)
    finally:
        pass
    loop.close()

#---------------------------------------------------

class Api(object):
    URL = 'https://api.telegram.org/bot%s/%s'

    def __init__(self, token, loop):
        self._token = token
        self._loop = loop

    async def _request(self, method, message):
        headers = {
            'Content-Type': 'application/json'
        }
        async with aiohttp.ClientSession(loop=self._loop) as session:
            async with session.post(self.URL % (self._token, method),
                                    data=json.dumps(message),
                                    headers=headers) as resp:
                try:
                    assert resp.status == 200
                except:
                    pass

    async def sendMessage(self, chatId, text):
        message = {
            'chat_id': chatId,
            'text': text
        }
        await self._request('sendMessage', message)


class Conversation(Api):
    def __init__(self, token, loop):
        super().__init__(token, loop)

    async def _handler(self, message):
        pass

    async def handler(self, request):
        message = await request.json()
        asyncio.ensure_future(self._handler(message['message']))
        return aiohttp.web.Response(status=200)


class EchoConversation(Conversation):
    def __init__(self, token, loop):
        super().__init__(token, loop)

    async def _handler(self, message):
        await self.sendMessage(message['chat']['id'],
                               message['text'])

#---------------------------------------------------

echobot = EchoConversation('358566966:AAEIAY_9VCUGPGjrSQZ2a5n6IR7h20WeAuI', loop)
app.router.add_post('/api/v1/echo', echobot.handler)